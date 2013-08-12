#ifndef _GAME_LOGIC_UNIT_H_
#define _GAME_LOGIC_UNIT_H_
#include "Die.hpp"
#include <SFML/Network.hpp>
#include <string>
class Unit
{
public:
    sf::Int32 currentHp;
    sf::Int32 maxHp;
    sf::Int32 shieldCounter;
    sf::Int32 burnCounter;
    sf::Int32 freezeCounter;
    sf::Int32 shockCounter;
    sf::Int32 diceCounter;
    std::string name;
    Unit();
    Unit(std::string name, sf::Int32 maxHp, sf::Int32 diceCount);
    sf::Int32 getNoMoveDamage();
    ~Unit();

};
sf::Packet& operator << (sf::Packet& packet, const Unit& message);
sf::Packet& operator >> (sf::Packet& packet, Unit& message);
#endif
