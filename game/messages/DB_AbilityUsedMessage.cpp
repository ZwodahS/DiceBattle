#include "DB_AbilityUsedMessage.hpp"

DB_AbilityUsedMessage::DB_AbilityUsedMessage()
    :Message(AbilityUsedMessage)
{
}

DB_AbilityUsedMessage::DB_AbilityUsedMessage(PlayerRole::ePlayerRole u, Ability a)
    :Message(AbilityUsedMessage), user(u), abilityUsed(a)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_AbilityUsedMessage& message)
{
    return packet << message.type << message.user << message.abilityUsed;
}
sf::Packet& operator >> (sf::Packet& packet, DB_AbilityUsedMessage& message)
{
    return packet >> message.type >> message.user >> message.abilityUsed;
}
