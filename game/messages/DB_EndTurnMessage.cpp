#include "DB_EndTurnMessage.hpp"

DB_EndTurnMessage::DB_EndTurnMessage(sf::Int32 damageTaken)
    :Message(EndTurnMessage)
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
