#ifndef _GAME_MESSAGES_DB_ENDTURNMESSAGE_H_
#define _GAME_MESSAGES_DB_ENDTURNMESSAGE_H_
#include "Message.hpp"
struct DB_EndTurnMessage : public Message
{
    DB_EndTurnMessage();
};

sf::Packet& operator << (sf::Packet& packet, const DB_EndTurnMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_EndTurnMessage& message);
#endif
