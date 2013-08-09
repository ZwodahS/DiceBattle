#ifndef _GAME_MESSAGES_DB_ACTIVETURNMESSAGE_H_
#define _GAME_MESSAGES_DB_ACTIVETURNMESSAGE_H_
#include "Message.hpp"
#include "../constants/PlayerRole.hpp"
#include "../logic/Die.hpp"
#include <vector>
struct DB_ActiveTurnMessage : public Message
{
    DB_ActiveTurnMessage();
    DB_ActiveTurnMessage(PlayerRole::ePlayerRole r, sf::Int32 burn, sf::Int32 availableDice, sf::Int32 frozenDice, std::vector<Die> rollable);
    PlayerRole::ePlayerRole currentPlayer;
    sf::Int32 burnDamage;
    sf::Int32 availableDice;
    sf::Int32 frozenDice;
    std::vector<Die> rollableDice;
};

sf::Packet& operator << (sf::Packet& packet, const DB_ActiveTurnMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_ActiveTurnMessage& message);
#endif
