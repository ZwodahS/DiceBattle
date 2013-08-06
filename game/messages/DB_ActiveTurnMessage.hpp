#ifndef _GAME_MESSAGES_DB_ACTIVETURNMESSAGE_H_
#define _GAME_MESSAGES_DB_ACTIVETURNMESSAGE_H_
#include "Message.hpp"
#include "../constants/PlayerRole.hpp"
struct DB_ActiveTurnMessage : public Message
{
    DB_ActiveTurnMessage();
    DB_ActiveTurnMessage(PlayerRole::ePlayerRole r, sf::Int32 burn, sf::Int32 availableDice, sf::Int32 frozenDice);
    PlayerRole::ePlayerRole currentPlayer;
    sf::Int32 burnDamage;
    sf::Int32 availableDice;
    sf::Int32 frozenDice;
};

sf::Packet& operator << (sf::Packet& packet, const DB_ActiveTurnMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_ActiveTurnMessage& message);
#endif
