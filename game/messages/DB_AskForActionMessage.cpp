#include "DB_AskForActionMessage.hpp"

DB_AskForActionMessage::DB_AskForActionMessage()
    :Message(AskForActionMessage)
{
}
DB_AskForActionMessage::DB_AskForActionMessage(PlayerRole::ePlayerRole r)
    :Message(AskForActionMessage), activePlayer(r)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_AskForActionMessage& message)
{
    return packet << message.type <<  message.activePlayer;
}
sf::Packet& operator >> (sf::Packet& packet, DB_AskForActionMessage& message)
{
    return packet >> message.type >> message.activePlayer;
}
