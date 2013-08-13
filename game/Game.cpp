#include "Game.hpp"
#include "screens/SetupScreen.hpp"
#include "screens/GameScreen.hpp"
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
    :width(GAME_WIDTH), height(GAME_HEIGHT), title(GAME_TITLE),
    window(sf::VideoMode(width,height),title),mouse(), _currentScreen(0)
{
    window.setFramerateLimit(50);
    loadAssets();
    rules.loadFromFile("data/default.rule");
    rules.sortAbilities();
}

Game::~Game()
{
    if(_currentScreen != 0)
    {
        delete _currentScreen;
    }
}

void Game::run()
{
    SetupScreen* setupScreen = new SetupScreen(*this);
    _currentScreen = setupScreen;
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
        }
    }
}

void Game::update(sf::Time& delta)
{
    if(_currentBattle != 0)
    {
        _currentBattle->update();
    }
    if(_currentScreen != 0)
    {
        _currentScreen->update(window, delta);
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

void Game::startGame(Battle* battle, PlayerRole::ePlayerRole role)
{
    if(battle != 0)
    {
        _currentBattle = battle;
        _viewer = new GameScreenViewer(role);
        _updater = new GeneralUpdater(role);
        _gameScreen = new GameScreen(*this, *_currentBattle, role, *_viewer, *_updater);
        _viewer->setGameScreen(_gameScreen);
        _currentScreen = _gameScreen;
        _currentBattle->addGameViewer(_viewer);
        _currentBattle->addGameUpdater(_updater);
    }
}

void Game::startLocalGame(Battle* battle, PlayerRole::ePlayerRole role, std::string player1 , std::string player2)
{
    if(battle != 0)
    {
        _currentBattle = battle;
        _viewer = new GameScreenViewer(role);
        _updater = new GeneralUpdater(role);
        _gameScreen = new GameScreen(*this, *_currentBattle, role, *_viewer, *_updater);
        _viewer->setGameScreen(_gameScreen);
        _currentScreen = _gameScreen;
        _currentBattle->addGameViewer(_viewer);
        _currentBattle->addGameUpdater(_updater);
        _currentBattle->startGame(rules, player1, player2);
    }
}
