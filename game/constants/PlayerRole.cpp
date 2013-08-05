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
            default : return None;
        }
    }
}

sf::Packet& operator << (sf::Packet& packet, const PlayerRole::ePlayerRole& message)
{
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, PlayerRole::ePlayerRole& message)
{
    return packet;
}
