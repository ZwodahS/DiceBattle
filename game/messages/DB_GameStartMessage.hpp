#ifndef _GAME_MESSAGES_DB_GAMESTARTMESSAGE_H_
#define _GAME_MESSAGES_DB_GAMESTARTMESSAGE_H_
#include "Message.hpp"
#include "../logic/Unit.hpp"
#include "../constants/PlayerRole.hpp"
/**
 * Tells the client the start of a game.
 */
struct DB_GameStartMessage : public Message
{
    DB_GameStartMessage();
    DB_GameStartMessage(PlayerRole::ePlayerRole, Unit p1 , Unit p2);
    /**
     * The role of this client.
     */
    PlayerRole::ePlayerRole role;
    /**
     * The name for player 1
     */
    Unit player1;
    /**
     * The name for player 2
     */
    Unit player2;
};

sf::Packet& operator << (sf::Packet& packet, const DB_GameStartMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_GameStartMessage& message);
#endif
