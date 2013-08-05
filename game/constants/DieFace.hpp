#ifndef _GAME_CONSTANTS_DIEFACE_H_
#define _GAME_CONSTANTS_DIEFACE_H_
#include <SFML/Network.hpp>
namespace DieFace
{
    enum eDieFace
    {
        Sword, 
        Shield,
        Heal,
        Fire,
        Ice,
        Shock,
    };

    sf::Int32 toInt(eDieFace face);
    eDieFace toDieFace(sf::Int32 intValue);
}

sf::Packet& operator << (sf::Packet& packet, const DieFace::eDieFace& message);
sf::Packet& operator >> (sf::Packet& packet, DieFace::eDieFace& message);
#endif
