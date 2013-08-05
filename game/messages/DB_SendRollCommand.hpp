#ifndef _GAME_MESSAGES_DB_SENDROLLCOMMAND_H_
#define _GAME_MESSAGES_DB_SENDROLLCOMMAND_H_
#include "Message.hpp"
#include <SFML/Network.hpp>
#include <vector>
struct DB_SendRollCommand : public Message
{
    DB_SendRollCommand();
    DB_SendRollCommand(std::vector<sf::Int32> diceId);
    std::vector<sf::Int32> diceId;
};

sf::Packet& operator << (sf::Packet& packet, const DB_SendRollCommand& message);
sf::Packet& operator >> (sf::Packet& packet, DB_SendRollCommand& message);
#endif
