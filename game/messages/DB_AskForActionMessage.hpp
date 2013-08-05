#ifndef _GAME_MESSAGES_DB_ASKFORACTIONMESSAGE_H_
#define _GAME_MESSAGES_DB_ASKFORACTIONMESSAGE_H_
#include "Message.hpp"
#include "../constants/PlayerRole.hpp"
struct DB_AskForActionMessage : public Message
{
    DB_AskForActionMessage();
    DB_AskForActionMessage(PlayerRole::ePlayerRole r);
    PlayerRole::ePlayerRole activePlayer;
};

sf::Packet& operator << (sf::Packet& packet, const DB_AskForActionMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_AskForActionMessage& message);
#endif
