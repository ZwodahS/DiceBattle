#ifndef _GAME_MESSAGES_DB_GAMESTARTMESSAGE_H_
#define _GAME_MESSAGES_DB_GAMESTARTMESSAGE_H_
#include "Message.hpp"
#include "../constants/PlayerRole.hpp"
struct DB_GameStartMessage : public Message
{
    DB_GameStartMessage(PlayerRole::ePlayerRole = PlayerRole::Observer);
    PlayerRole::ePlayerRole role;
};

sf::Packet& operator << (sf::Packet& packet, const DB_GameStartMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_GameStartMessage& message);
#endif
