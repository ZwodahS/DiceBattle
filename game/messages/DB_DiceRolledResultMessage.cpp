#include "DB_DiceRolledResultMessage.hpp"
DB_DiceRolledResultMessage::DB_DiceRolledResultMessage()
    :Message(DiceRolledResultMessage)
{
}
DB_DiceRolledResultMessage::DB_DiceRolledResultMessage(std::vector<Die> dice)
    :Message(DiceRolledResultMessage), rolledDice(dice)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_DiceRolledResultMessage& message)
{
    packet << message.type;
    sf::Int32 size = message.rolledDice.size();
    packet << size;
    for(std::vector<Die>::const_iterator it = message.rolledDice.begin() ; it != message.rolledDice.end() ; ++it)
    {
        packet << *it; 
    }
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, DB_DiceRolledResultMessage& message)
{
    packet >> message.type;
    sf::Int32 size;
    packet >> size;
    message.rolledDice.clear();
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        Die d;
        packet >> d;
        message.rolledDice.push_back(d);
    }
    return packet;
}
