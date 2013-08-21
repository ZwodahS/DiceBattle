#include "DB_EndTurnMessage.hpp"

DB_EndTurnMessage::DB_EndTurnMessage(sf::Int32 dt)
    :Message(EndTurnMessage), damageTaken(dt)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_EndTurnMessage& message)
{
    return packet << message.type << message.damageTaken;
}
sf::Packet& operator >> (sf::Packet& packet, DB_EndTurnMessage& message)
{
    return packet >> message.type >> message.damageTaken;
}
