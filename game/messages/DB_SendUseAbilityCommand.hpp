#ifndef _GAME_MESSAGES_DB_SENDUSEABILITYCOMMAND_H_
#define _GAME_MESSAGES_DB_SENDUSEABILITYCOMMAND_H_
#include "Message.hpp"
#include "../logic/Ability.hpp"
struct DB_SendUseAbilityCommand : public Message
{
    DB_SendUseAbilityCommand();
    DB_SendUseAbilityCommand(PlayerRole::ePlayerRole user, Ability abilityUsed);
    PlayerRole::ePlayerRole user;
    Ability abilityUsed;
};

sf::Packet& operator << (sf::Packet& packet, const DB_SendUseAbilityCommand& message);
sf::Packet& operator >> (sf::Packet& packet, DB_SendUseAbilityCommand& message);
#endif
