#include "DB_ActiveTurnMessage.hpp"

DB_ActiveTurnMessage::DB_ActiveTurnMessage()
    :Message(ActiveTurnMessage)
{
}

DB_ActiveTurnMessage::DB_ActiveTurnMessage(PlayerRole::ePlayerRole r, sf::Int32 burn, sf::Int32 availableDice, sf::Int32 frozenDice)
    :Message(ActiveTurnMessage), currentPlayer(r)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_ActiveTurnMessage& message)
{
    return packet << message.type << message.currentPlayer << message.burnDamage << message.availableDice << message.frozenDice;
}
sf::Packet& operator >> (sf::Packet& packet, DB_ActiveTurnMessage& message)
{
    return packet >> message.type >> message.currentPlayer >> message.burnDamage >> message.availableDice >> message.frozenDice;
}
