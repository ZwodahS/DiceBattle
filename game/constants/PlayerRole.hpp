#ifndef _GAME_CONSTANTS_PLAYERROLE
#define _GAME_CONSTANTS_PLAYERROLE
#include <SFML/Network.hpp>
namespace PlayerRole
{
    enum ePlayerRole
    {
        PlayerOne = 0,
        PlayerTwo = 1,
        Observer = 2,
        None = 3,
    };

    sf::Int32 toInt(ePlayerRole role);
    ePlayerRole toPlayerRole(sf::Int32);
}

sf::Packet& operator << (sf::Packet& packet, const PlayerRole::ePlayerRole& message);
sf::Packet& operator >> (sf::Packet& packet, PlayerRole::ePlayerRole& message);
#endif
