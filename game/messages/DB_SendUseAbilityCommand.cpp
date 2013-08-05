#include "DB_SendUseAbilityCommand.hpp"

DB_SendUseAbilityCommand::DB_SendUseAbilityCommand()
    :Message(SendUseAbilityCommand)
{
}

DB_SendUseAbilityCommand::DB_SendUseAbilityCommand(PlayerRole::ePlayerRole u, Ability a)
    :Message(SendUseAbilityCommand), user(u), abilityUsed(a)
{
}

sf::Packet& operator << (sf::Packet& packet, const DB_SendUseAbilityCommand& message)
{
    return packet << message.type << message.user << message.abilityUsed;
}
sf::Packet& operator >> (sf::Packet& packet, DB_SendUseAbilityCommand& message)
{
    return packet >> message.type >> message.user >> message.abilityUsed;
}
