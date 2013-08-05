#ifndef _GAME_LOGIC_UNIT_H_
#define _GAME_LOGIC_UNIT_H_
#include "Die.hpp"
#include <SFML/Network.hpp>
class Unit
{
public:
    sf::Int32 currentHp;
    sf::Int32 maxHp;
    sf::Int32 shieldCounter;
    sf::Int32 burnCounter;
    sf::Int32 diceCounter;
    Unit();
    Unit(sf::Int32 maxHp, sf::Int32 diceCount);
    ~Unit();

};
#endif
