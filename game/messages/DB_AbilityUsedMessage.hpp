#ifndef _GAME_MSSAGES_DB_ABILITYUSEDMESSAGE_H_
#define _GAME_MSSAGES_DB_ABILITYUSEDMESSAGE_H_
#include "Message.hpp"
#include "../logic/Ability.hpp"
#include "../constants/PlayerRole.hpp"
#include <vector>
struct DB_AbilityUsedMessage : public Message
{
    DB_AbilityUsedMessage();
    DB_AbilityUsedMessage(PlayerRole::ePlayerRole user, Ability abilityUsed, std::vector<sf::Int32> diceUsed);
    PlayerRole::ePlayerRole user;
    Ability abilityUsed;
    std::vector<sf::Int32> diceUsed;
};

sf::Packet& operator << (sf::Packet& packet, const DB_AbilityUsedMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_AbilityUsedMessage& message);
#endif
