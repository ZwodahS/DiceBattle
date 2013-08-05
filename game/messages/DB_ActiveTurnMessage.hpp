#ifndef _GAME_MESSAGES_DB_ACTIVETURNMESSAGE_H_
#define _GAME_MESSAGES_DB_ACTIVETURNMESSAGE_H_
#include "Message.hpp"
#include "../constants/PlayerRole.hpp"
struct DB_ActiveTurnMessage : public Message
{
    DB_ActiveTurnMessage();
    DB_ActiveTurnMessage(PlayerRole::ePlayerRole r);
    PlayerRole::ePlayerRole currentPlayer;
};

sf::Packet& operator << (sf::Packet& packet, const DB_ActiveTurnMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_ActiveTurnMessage& message);
#endif
