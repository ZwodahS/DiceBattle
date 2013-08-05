#include "DieFace.hpp"

namespace DieFace
{
    sf::Int32 toInt(eDieFace face)
    {
        return face;
    }

    eDieFace toDieFace(sf::Int32 intValue)
    {
        switch(intValue)
        {
            case Sword : return Sword;
            case Shield : return Shield;
            case Heal : return Heal;
            case Fire : return Fire;
            case Ice : return Ice;
            case Shock : return Shock;
            default : return Sword;
        }
    }
}

sf::Packet& operator << (sf::Packet& packet, const DieFace::eDieFace& message)
{
    return packet << DieFace::toInt(message);
}
sf::Packet& operator >> (sf::Packet& packet, DieFace::eDieFace& message)
{
    sf::Int32 tmp;
    packet >> tmp;
    message = DieFace::toDieFace(tmp);
    return packet;
}
