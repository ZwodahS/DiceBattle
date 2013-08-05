#include "DB_GameStartMessage.hpp"

DB_GameStartMessage::DB_GameStartMessage(PlayerRole::ePlayerRole r)
    :Message(GameStartMessage), role(r)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_GameStartMessage& message)
{
    return packet << message.type << message.role;
}
sf::Packet& operator >> (sf::Packet& packet, DB_GameStartMessage& message)
{
    return packet >> message.type >> message.role;
}
