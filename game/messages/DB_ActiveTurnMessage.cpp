#include "DB_ActiveTurnMessage.hpp"

DB_ActiveTurnMessage::DB_ActiveTurnMessage()
    :Message(ActiveTurnMessage)
{
}

DB_ActiveTurnMessage::DB_ActiveTurnMessage(PlayerRole::ePlayerRole r, sf::Int32 burn, sf::Int32 availableDice, sf::Int32 frozenDice, std::vector<Die> rollable)
    :Message(ActiveTurnMessage), currentPlayer(r), rollableDice(rollable)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_ActiveTurnMessage& message)
{
    packet << message.type << message.currentPlayer << message.burnDamage << message.availableDice << message.frozenDice;
    sf::Int32 size = message.rollableDice.size();
    packet << size;
    for(std::vector<Die>::const_iterator it = message.rollableDice.begin() ; it != message.rollableDice.end() ; ++it)
    {
        packet << *it; 
    }
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, DB_ActiveTurnMessage& message)
{
    packet >> message.type >> message.currentPlayer >> message.burnDamage >> message.availableDice >> message.frozenDice;
    sf::Int32 size;
    packet >> size;
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        Die d;
        packet >> d;
        message.rollableDice.push_back(d);
    }
    return packet;
}
