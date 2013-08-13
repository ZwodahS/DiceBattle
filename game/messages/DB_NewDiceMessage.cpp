#include "DB_NewDiceMessage.hpp"

DB_NewDiceMessage::DB_NewDiceMessage()
    :Message(NewDiceMessage)
{
}

DB_NewDiceMessage::DB_NewDiceMessage(std::vector<Die> d)
    :Message(NewDiceMessage), dice(d)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_NewDiceMessage& message)
{
    sf::Int32 size = message.dice.size();
    packet << size;
    for(std::vector<Die>::const_iterator it = message.dice.begin() ; it != message.dice.end() ; ++it)
    {
        packet << *it; 
    }
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, DB_NewDiceMessage& message)
{
    sf::Int32 size;
    packet >> size;
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        Die d;
        packet >> d;
        message.dice.push_back(d);
    }
    return packet;
}
