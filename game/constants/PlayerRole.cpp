#include "PlayerRole.hpp"

namespace PlayerRole
{
    sf::Int32 toInt(ePlayerRole role)
    {
        return role;
    }
    ePlayerRole toPlayerRole(sf::Int32 intValue)
    {
        switch(intValue)
        {
            case PlayerOne : return PlayerOne;
            case PlayerTwo : return PlayerTwo;
            case Observer : return Observer;
            case Both : return Both;
            default : return None;
        }
    }
    ePlayerRole randomPlayer()
    {
        return toPlayerRole(rand() % 2);
    }
    ePlayerRole opponentOf(ePlayerRole player)
    {
        switch(player)
        {
            case PlayerOne : return PlayerTwo;
            case PlayerTwo : return PlayerOne;
            default : return None;
        }
    }
}

sf::Packet& operator << (sf::Packet& packet, const PlayerRole::ePlayerRole& message)
{
    return packet << toInt(message);
}
sf::Packet& operator >> (sf::Packet& packet, PlayerRole::ePlayerRole& message)
{
    sf::Int32 tmp;
    packet >> tmp;
    message = PlayerRole::toPlayerRole(tmp);
    return packet;
}
