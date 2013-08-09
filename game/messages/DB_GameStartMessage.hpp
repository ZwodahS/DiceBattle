#ifndef _GAME_MESSAGES_DB_GAMESTARTMESSAGE_H_
#define _GAME_MESSAGES_DB_GAMESTARTMESSAGE_H_
#include "Message.hpp"
#include "../logic/Unit.hpp"
#include "../logic/Rules.hpp"
#include "../constants/PlayerRole.hpp"
/**
 * Tells the client the start of a game.
 */
struct DB_GameStartMessage : public Message
{
    DB_GameStartMessage();
    DB_GameStartMessage(Rules rules, Unit p1 , Unit p2);
    Unit player1;
    Unit player2;
    Rules rules;
};

sf::Packet& operator << (sf::Packet& packet, const DB_GameStartMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_GameStartMessage& message);
#endif
