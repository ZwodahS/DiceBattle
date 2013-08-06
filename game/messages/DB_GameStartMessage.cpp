#include "DB_GameStartMessage.hpp"

DB_GameStartMessage::DB_GameStartMessage()
    :Message(GameStartMessage), role(PlayerRole::Observer)
{
}

DB_GameStartMessage::DB_GameStartMessage(PlayerRole::ePlayerRole r, Unit p1, Unit p2)
    :Message(GameStartMessage), role(r), player1(p1), player2(p2)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_GameStartMessage& message)
{
    return packet << message.type << message.role << message.player1 << message.player2;
}
sf::Packet& operator >> (sf::Packet& packet, DB_GameStartMessage& message)
{
    return packet >> message.type >> message.role >> message.player1 >> message.player2;
}
