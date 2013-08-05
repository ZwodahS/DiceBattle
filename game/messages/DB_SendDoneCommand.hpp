#ifndef _GAME_MESSAGES_DB_SENDDONECOMMAND_H_
#define _GAME_MESSAGES_DB_SENDDONECOMMAND_H_
#include "Message.hpp"
struct DB_SendDoneCommand : public Message
{
    DB_SendDoneCommand();
};

sf::Packet& operator << (sf::Packet& packet, const DB_SendDoneCommand& message);
sf::Packet& operator >> (sf::Packet& packet, DB_SendDoneCommand& message);
#endif
