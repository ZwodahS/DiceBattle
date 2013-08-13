#ifndef _GAME_MESSAGES_DB_NEWDICEMESSAGE_H_
#define _GAME_MESSAGES_DB_NEWDICEMESSAGE_H_
#include "Message.hpp"
#include "../logic/Die.hpp"
#include <SFML/Network.hpp>
struct DB_NewDiceMessage : public Message
{
    DB_NewDiceMessage();
    DB_NewDiceMessage(std::vector<Die> dice);
    std::vector<Die> dice;
};
sf::Packet& operator << (sf::Packet& packet, const DB_NewDiceMessage& message);
sf::Packet& operator >> (sf::Packet& packet, DB_NewDiceMessage& message);

#endif
