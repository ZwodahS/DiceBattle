#include "DB_EndGameMessage.hpp"

DB_EndGameMessage::DB_EndGameMessage()
    :Message(EndGameMessage)
{
}

DB_EndGameMessage::DB_EndGameMessage(PlayerRole::ePlayerRole r)
    :Message(EndGameMessage), winner(r)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_EndGameMessage& message)
{
    return packet << message.type << message.winner;
}
sf::Packet& operator >> (sf::Packet& packet, DB_EndGameMessage& message)
{
    return packet >> message.type >> message.winner;;
}
