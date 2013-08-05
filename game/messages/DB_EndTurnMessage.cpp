#include "DB_EndTurnMessage.hpp"

DB_EndTurnMessage::DB_EndTurnMessage()
    :Message(EndTurnMessage)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_EndTurnMessage& message)
{
    return packet << message.type;
}
sf::Packet& operator >> (sf::Packet& packet, DB_EndTurnMessage& message)
{
    return packet >> message.type;
}
