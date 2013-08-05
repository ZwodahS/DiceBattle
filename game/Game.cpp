#include "Game.hpp"
#include "screens/Screen.hpp"
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
                mouse._wheelDelta = event.mouseWheel.delta;
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
