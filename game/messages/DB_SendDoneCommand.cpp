#include "DB_SendDoneCommand.hpp"

DB_SendDoneCommand::DB_SendDoneCommand()
    :Message(SendDoneCommand)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_SendDoneCommand& message)
{
    return packet << message.type;
}
sf::Packet& operator >> (sf::Packet& packet, DB_SendDoneCommand& message)
{
    return packet >> message.type;
}
