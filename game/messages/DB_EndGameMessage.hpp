#ifndef _GAME_MESSSAGES_DB_ENDGAMEMESSAGE_H_
#define _GAME_MESSSAGES_DB_ENDGAMEMESSAGE_H_
#include "Message.hpp"
#include "../constants/PlayerRole.hpp"
struct DB_EndGameMessage : public Message
{
    DB_EndGameMessage();
    DB_EndGameMessage(PlayerRole::ePlayerRole r);
    PlayerRole::ePlayerRole winner;
};

sf::Packet& operator << (sf::Packet& packet, const DB_EndGameMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_EndGameMessage& message);
#endif
