#include "Game.hpp"
#include "constants/GameType.hpp"
#include "screens/SetupScreen.hpp"
#include "screens/GameScreen.hpp"
#include "screens/MainScreen.hpp"
#include "screens/Screen.hpp"
#include "screens/GameScreenViewer.hpp"
#include "logic/GeneralUpdater.hpp"
#include "logic/BattleServer.hpp"
#include "logic/Battle.hpp"
#include "logic/TcpClient.hpp"
#include "../z_framework/zf_common/debugging.hpp"
#include "../z_framework/zf_network/zf_gamesetup/GameSetup.hpp"
#include "../z_framework/zf_network/Connection.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#define CLEAR_COLOR sf::Color(20,20,20,255)
#define GAME_TITLE "Game Name"
#define GAME_WIDTH 640
#define GAME_HEIGHT 480
Game::Game()
    :width(GAME_WIDTH), height(GAME_HEIGHT), title(GAME_TITLE) 
    , window(sf::VideoMode(width,height),title),mouse(), _currentScreen(0), _nextScreen(0), _currentBattle(0)
    , _mainScreen(0), _gameScreen(0), _setupScreen(0), _battlePacketLayer(connection), _gameSetup(0), isFocused(true)
{
    window.setFramerateLimit(50);
    loadAssets();
    rules.loadFromFile("data/default.rule");
    rules.sortAbilities();
    connection.addDownStream(_battlePacketLayer);
    background = assets.background.createSprite();
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
            update(delta);
            draw(delta);
            if(_currentScreen != 0 && _currentScreen->screenState == Screen::Active)
            {
                connection.listen();
                connection.receive();
            }
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
    if(_currentScreen != 0)
    {
        _currentScreen->update(window, delta);
    }
    if(_currentScreen != 0 && _currentScreen->screenState == Screen::Exited)
    {
        if(_currentScreen == _mainScreen)
        {
            delete _mainScreen;
            _mainScreen = 0;
        }
        else if(_currentScreen == _gameScreen)
        {
            // clean up the battle server
            _battlePacketLayer.resetLayer();
            // clean the battle obj
            delete _currentBattle;
            _currentBattle = 0;
            // go back to the correct setup
            delete _gameScreen;
            _gameScreen = 0;
        }
        else if(_setupScreen == _currentScreen)
        {
            delete _setupScreen;
            _setupScreen = 0;
            // clear up gamesetup as well.
            connection.removeDownStream(*_gameSetup);
            delete _gameSetup;
            _gameSetup = 0;
        }
        _currentScreen = _nextScreen;
        _nextScreen = 0;
        _currentScreen->screenEnter();
    }
    if(_currentBattle != 0)
    {
        _currentBattle->update();
    }
}

void Game::draw(sf::Time& delta)
{
    window.clear(CLEAR_COLOR);
    // always draw background
    window.draw(background);
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
    _setupScreen = new SetupScreen(*this, GameType::Local);
    _currentScreen->screenExit();
    _nextScreen = _setupScreen;
}

void Game::startLocalGame(std::string player1, std::string player2)
{
    // make sure we are in the setup screen
    if(_currentScreen != _setupScreen)
    {
        return;
    }
    // free the previous battle if any
    if(_currentBattle != 0)
    {
        delete _currentBattle;
        _currentBattle = 0;
    }
    _currentBattle = new Battle();
    _gameScreen = new GameScreen(*this, *_currentBattle, PlayerRole::Both, GameType::Local);
    _currentBattle->startGame(rules,player1,player2);
    _currentScreen->screenExit();
    _nextScreen = _gameScreen;
}

void Game::startNetworkGame(zf::GameSetup* setup, PlayerRole::ePlayerRole role)
{
    // make sure we are in the setup screen
    if(_currentScreen != _setupScreen)
    {
        return;
    }
    // free the previous battle if any
    if(_currentBattle != 0)
    {
        delete _currentBattle;
        _currentBattle = 0;
    }
    std::vector<std::string> p1 = setup->getUniqueId("1");
    std::vector<std::string> p2 = setup->getUniqueId("2");
    if(p1.size() != 1 || p2.size() != 1)
    {
        return;
    }
    _currentBattle = new Battle();
    // add all the client as listener.
    for(std::vector<zf::GameSetup::Player>::const_iterator it = setup->getPlayers().begin() ; it != setup->getPlayers().end() ; ++it)
    {
        zf::Connection* conn = connection.getConnection((*it).uniqueId); 
        if(conn != 0)
        {
            PlayerRole::ePlayerRole role = (*it).role == "1" ? PlayerRole::PlayerOne : (*it).role == "2" ? PlayerRole::PlayerTwo : PlayerRole::Observer;
            TcpClient& client = _battlePacketLayer.getClient(*conn, role);
            _currentBattle->addGameViewer(&client.viewer);
            _currentBattle->addGameUpdater(&client.updater);
        }
    }
    // this will inform all client that game has started and get ready to receive battle message
    setup->startGame();
    _gameScreen = new GameScreen(*this, *_currentBattle, role, GameType::Host);
    _currentBattle->startGame(rules, p1[0], p2[0]);
    _currentScreen->screenExit();
    _nextScreen = _gameScreen;
}

void Game::joinNetworkGame(zf::GameSetup* setup, PlayerRole::ePlayerRole role)
{
    // make sure we are in the setup screen
    if(_currentScreen != _setupScreen)
    {
        return;
    }
    // free the previous battle if any
    if(_currentBattle != 0)
    {
        delete _currentBattle;
        _currentBattle = 0;
    }
    // create the server
    BattleServer* server = new BattleServer(_battlePacketLayer);
    _battlePacketLayer.setBattleServer(server);
    // create the current battle using the server
    _currentBattle = new Battle(*server);
    // create the game screen and exit
    _gameScreen = new GameScreen(*this, *_currentBattle, role, GameType::Remote);
    _currentScreen->screenExit();
    _nextScreen = _gameScreen;
}

bool Game::setupHosting(unsigned short port, std::string name)
{
    bool success = connection.startServer(port);
    if(success)
    {
        connection.verifiedName = name;
        _gameSetup = getNewGameSetup(true);
        _setupScreen = new SetupScreen(*this, GameType::Host, _gameSetup);
        _nextScreen = _setupScreen;
        _currentScreen->screenExit();
        _gameSetup->ready();
        _gameSetup->setRole("1");
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

/*
 * This is hacked in at the last minute. Probably extremely hackish
 */
void Game::backToSetup(GameType::eGameType gameType, PlayerRole::ePlayerRole myRole)
{
    if(_gameScreen == 0 || _gameScreen != _currentScreen || _currentScreen->screenState != Screen::Active)
    {
        return;
    }
    else
    {
        if(gameType == GameType::Local)
        {
            _setupScreen = new SetupScreen(*this, GameType::Local);
            _currentScreen->screenExit();
            _nextScreen = _setupScreen;
        }
        else if(gameType == GameType::Host)
        {
            // make sure we are still hosting
            if(connection.isHosting())
            {
                _gameSetup = getNewGameSetup(true);
                _setupScreen = new SetupScreen(*this, GameType::Host, _gameSetup);
                _nextScreen = _setupScreen;
                _currentScreen->screenExit();
                _gameSetup->ready();
                _gameSetup->setRole("1");
            }
        }
        else if(gameType == GameType::Remote)
        {
            // make sure we are still connected
            if(connection.isConnected())
            {
                _gameSetup = getNewGameSetup(false);
                _setupScreen = new SetupScreen(*this, GameType::Remote, _gameSetup);
                _nextScreen = _setupScreen;
                _currentScreen->screenExit();
                _gameSetup->joinServer();
            }
        }
    }    
}

zf::GameSetup* Game::getNewGameSetup(bool isHosting)
{
    if(_gameSetup != 0)
    {
        connection.removeDownStream(*_gameSetup);
        delete _gameSetup;
        _gameSetup = 0;
    }
    _gameSetup = new zf::GameSetup(connection.verifiedName, connection, GAMESETUP_HEADER, isHosting);
    connection.addDownStream(*_gameSetup);
    return _gameSetup;
}
