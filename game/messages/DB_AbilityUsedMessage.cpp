#include "DB_AbilityUsedMessage.hpp"

DB_AbilityUsedMessage::DB_AbilityUsedMessage()
    :Message(AbilityUsedMessage)
{
}

DB_AbilityUsedMessage::DB_AbilityUsedMessage(PlayerRole::ePlayerRole u, Ability a, std::vector<sf::Int32> d)
    :Message(AbilityUsedMessage), user(u), abilityUsed(a), diceUsed(d)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_AbilityUsedMessage& message)
{
    packet << message.type << message.user << message.abilityUsed;
    sf::Int32 size = message.diceUsed.size();
    packet << size;
    for(std::vector<sf::Int32>::const_iterator it = message.diceUsed.begin() ; it != message.diceUsed.end() ; ++it)
    {
        packet << *it ; 
    }
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, DB_AbilityUsedMessage& message)
{
    packet >> message.type >> message.user >> message.abilityUsed;
    sf::Int32 size;
    packet >> size;
    message.diceUsed.clear();
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        sf::Int32 tmp;
        packet >> tmp;
        message.diceUsed.push_back(tmp);
    }
    return packet;
}
