#include "DB_SendRollCommand.hpp"

DB_SendRollCommand::DB_SendRollCommand()
    :Message(SendRollCommand)
{
}

DB_SendRollCommand::DB_SendRollCommand(std::vector<sf::Int32> d)
    :Message(SendRollCommand), diceId(d)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_SendRollCommand& message)
{
    packet << message.type;
    sf::Int32 size = message.diceId.size();
    packet << size;
    for(std::vector<sf::Int32>::const_iterator it = message.diceId.begin() ; it != message.diceId.end() ; ++it)
    {
        packet << *it; 
    }
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, DB_SendRollCommand& message)
{
    packet >> message.type;
    sf::Int32 size;
    packet >> size;
    message.diceId.clear();
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        sf::Int32 dieId;
        packet >> dieId;
        message.diceId.push_back(dieId);
    }
    return packet;
}
