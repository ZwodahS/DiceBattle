#ifndef _GAME_MESSAGES_DB_DICEROLLEDRESULTMESSAGE_H_
#define _GAME_MESSAGES_DB_DICEROLLEDRESULTMESSAGE_H_
#include "Message.hpp"
#include "../logic/Die.hpp"
struct DB_DiceRolledResultMessage : public Message
{
    DB_DiceRolledResultMessage();
    DB_DiceRolledResultMessage(std::vector<Die> dice);
    std::vector<Die> rolledDice;  
};

sf::Packet& operator << (sf::Packet& packet, const DB_DiceRolledResultMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_DiceRolledResultMessage& message);
#endif
