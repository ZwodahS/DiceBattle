#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_

#include "Assets.hpp"
#include "logic/Rules.hpp"
#include "screens/GameScreenViewer.hpp"
#include "logic/GeneralUpdater.hpp"
#include "../z_framework/zf_sfml/Mouse.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Screen;
class GameScreen;
class SetupScreen;
class Battle;
class Game
{
    public:
        Game();
        ~Game();
        void run(); 




        const sf::Int32 width;
        const sf::Int32 height;
        std::string title;
        sf::RenderWindow window; 
        zf::Mouse mouse;
        Assets assets;
        Rules rules;
        bool isFocused;
        void loadAssets();
    private:
        void update(sf::Time& delta);
        void draw(sf::Time& delta);
        void startGame(Battle* battle, PlayerRole::ePlayerRole role); 
        void startLocalGame(Battle* battle, PlayerRole::ePlayerRole role, std::string player1, std::string player2);
        Screen* _currentScreen;
        GameScreen* _gameScreen;        
        Battle* _currentBattle;
        GameScreenViewer* _viewer;
        GeneralUpdater* _updater;
};


#endif

