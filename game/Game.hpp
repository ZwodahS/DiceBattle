#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_

#include "Assets.hpp"
#include "logic/Rules.hpp"
#include "../z_framework/zf_sfml/Mouse.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Screen;
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
        void loadAssets();
    private:
        void update(sf::Time& delta);
        void draw(sf::Time& delta);
        
        Screen* _currentScreen;        
        Battle* _currentBattle;
};


#endif

