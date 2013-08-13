#ifndef _GAME_SCREENS_SCREEN_H_
#define _GAME_SCREENS_SCREEN_H_

#include <SFML/Graphics.hpp>

class Game;
class Screen
{
public:
    Screen(Game& game);
    ~Screen();
    
    virtual void draw(sf::RenderWindow& window, const sf::Time& delta) = 0;
    virtual void update(sf::RenderWindow& window, const sf::Time& delta) = 0;
    virtual void textInput(char c) = 0;
    
protected:
    
    Game& _game;
        

};
#endif
