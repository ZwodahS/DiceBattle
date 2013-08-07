#ifndef _GAME_CONSTANTS_DIEFACE_H_
#define _GAME_CONSTANTS_DIEFACE_H_
#include <SFML/Network.hpp>
namespace DieFace
{
    enum eDieFace
    {
        Sword = 0, 
        Shield = 1,
        Heal = 2,
        Fire = 3,
        Ice = 4,
        Shock = 5,
    };

    sf::Int32 toInt(eDieFace face);
    eDieFace toDieFace(sf::Int32 intValue);
    eDieFace randomFace();
    eDieFace randomFace(eDieFace f);
}

sf::Packet& operator << (sf::Packet& packet, const DieFace::eDieFace& message);
sf::Packet& operator >> (sf::Packet& packet, DieFace::eDieFace& message);
#endif
