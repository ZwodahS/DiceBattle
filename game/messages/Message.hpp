#ifndef _GAME_MESSAGES_MESSAGE_H_
#define _GAME_MESSAGES_MESSAGE_H_
#include <SFML/Network.hpp>
struct Message
{
    enum MessageType
    {
        //// Server To Client ////
        GameStartMessage ,
        ActiveTurnMessage,
        AskForActionMessage,
        DiceRolledResultMessage,
        AbilityUsedMessage,
        NewDiceMessage,
        EndTurnMessage,
        EndGameMessage,
        SendDoneCommand,
        SendRollCommand,
        SendUseAbilityCommand,
    };
    Message(MessageType t);
    static sf::Int32 toInt(MessageType type);
    static MessageType toType(sf::Int32 intValue);
    MessageType type;
};

sf::Packet& operator << (sf::Packet& packet, const Message::MessageType& message);
sf::Packet& operator >> (sf::Packet& packet, Message::MessageType& message);
#endif
