#include "DB_GameStartMessage.hpp"

DB_GameStartMessage::DB_GameStartMessage()
    :Message(GameStartMessage)
{
}

DB_GameStartMessage::DB_GameStartMessage(Unit p1, Unit p2)
    :Message(GameStartMessage), player1(p1), player2(p2)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_GameStartMessage& message)
{
    return packet << message.type << message.player1 << message.player2;
}
sf::Packet& operator >> (sf::Packet& packet, DB_GameStartMessage& message)
{
    return packet >> message.type >> message.player1 >> message.player2;
}
