#include "Game.hpp"
#include "screens/SetupScreen.hpp"
#include "screens/GameScreen.hpp"
#include "screens/MainScreen.hpp"
#include "screens/Screen.hpp"
#include "screens/GameScreenViewer.hpp"
#include "logic/GeneralUpdater.hpp"
#include "logic/Battle.hpp"
#include "../z_framework/zf_common/debugging.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#define CLEAR_COLOR sf::Color(20,20,20,255)
#define GAME_TITLE "Game Name"
#define GAME_WIDTH 640
#define GAME_HEIGHT 480
Game::Game()
    :width(GAME_WIDTH), height(GAME_HEIGHT), title(GAME_TITLE) 
    , window(sf::VideoMode(width,height),title),mouse(), _currentScreen(0), _nextScreen(0), _currentBattle(0)
    , _mainScreen(0), _gameScreen(0), _setupScreen(0)
{
    window.setFramerateLimit(50);
    loadAssets();
    rules.loadFromFile("data/default.rule");
    rules.sortAbilities();
}

Game::~Game()
{
}

void Game::run()
{
    _mainScreen = new MainScreen(*this);
    _currentScreen = _mainScreen;
    _currentScreen->screenEnter();
    connection.addListener(*this);
    // set up the clock for delta
    sf::Clock clock; 
    bool quit = false;
    while(!quit && window.isOpen())
    {
        // update clock 
        sf::Time delta = clock.restart();
        // update mouse.
        mouse.update(delta);
        // check for events, especially mousewheel
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                quit = true;
            }
            else if(event.type == sf::Event::MouseWheelMoved)
            {
                mouse.wheelDelta = event.mouseWheel.delta;
            }
            else if(event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode < 128)
                {
                    if(_currentScreen != 0)
                    {
                        _currentScreen->textInput(static_cast<char>(event.text.unicode));
                    }
                }
            }
            else if(event.type == sf::Event::LostFocus)
            {
                isFocused = false;
            }
            else if(event.type == sf::Event::GainedFocus)
            {
                isFocused = true;
            }
        }
        // if not quit , update then draw.
        if(!quit)
        {
            connection.listen();
            connection.receive();
            update(delta);
            draw(delta);
        }
    }
}

void Game::update(sf::Time& delta)
{
    if(_waitingReplyTimeout >= 0)
    {
        _waitingReplyTimeout -= delta.asSeconds();
        if(_waitingReplyTimeout <= 0)
        {
            _waitingReplyTimeout = 0;
            if(_mainScreen != 0)
            {
                _mainScreen->replyTimeout();
            }
        }
    }
    if(_currentBattle != 0)
    {
        _currentBattle->update();
    }
    if(_currentScreen != 0)
    {
        _currentScreen->update(window, delta);
    }
    if(_currentScreen->screenState == Screen::Exited)
    {
        if(_currentScreen == _mainScreen)
        {
            delete _mainScreen;
            _mainScreen = 0;
        }
        else if(_currentScreen == _gameScreen)
        {
            delete _gameScreen;
            _gameScreen = 0;
        }
        else if(_setupScreen == _currentScreen)
        {
            delete _setupScreen;
            _setupScreen = 0;
        }
        _currentScreen = _nextScreen;
        _nextScreen = 0;
        _currentScreen->screenEnter();
    }
}

void Game::draw(sf::Time& delta)
{
    window.clear(CLEAR_COLOR);
    if(_currentScreen != 0)
    {
        _currentScreen->draw(window,delta);   
    }
    window.display();
}

void Game::appendSetupMessageHeader(sf::Packet& packet)
{
    connection.appendHeader(packet);
    packet << SetupMessage;
}

void Game::appendGameMessageHeader(sf::Packet& packet)
{
    connection.appendHeader(packet);
    packet << GameMessage;
}

void Game::setupLocalGame()
{
    if(_setupScreen != 0)
    {
        delete _setupScreen;
    }
    _setupScreen = new SetupScreen(*this, SetupScreen::Local);
    _currentScreen->screenExit();
    _nextScreen = _setupScreen;
}

void Game::startLocalGame(std::string player1, std::string player2)
{
    _currentBattle = new Battle();
    _gameScreen = new GameScreen(*this, *_currentBattle, PlayerRole::Both);
    _currentBattle->startGame(rules,player1,player2);
    _currentScreen->screenExit();
    _nextScreen = _gameScreen;
}

bool Game::setupHosting(unsigned short port, std::string name)
{
    bool success = connection.startServer(port);
    if(success)
    {
        connection.verifiedName = name;
        zf::GameSetup* gs = new zf::GameSetup(connection.verifiedName, connection, GAMESETUP_HEADER, true);
        _setupScreen = new SetupScreen(*this, SetupScreen::Host, gs);
        connection.addDownStream(gs);
        _nextScreen = _setupScreen;
        _currentScreen->screenExit();
        gs->ready();
        gs->setRole("1");
    }
    return success;
}

bool Game::setupJoin(std::string name, std::string ipAddr, unsigned short port)
{
    // need to send the verify message and then wait for reply.
    if(connection.isConnected())
    {
        connection.disconnect();
    }
    else if(connection.isHosting())
    {
        connection.stopServer();
    }
    connection.verifiedName = name;
    bool success = connection.connectTo(ipAddr, port);
    if(success)
    {
        // wait for reply
        // Disable mainscreen input
        _mainScreen->waitingForReply();
        // set wait time
        _waitingReplyTimeout = 10;
    }
}


