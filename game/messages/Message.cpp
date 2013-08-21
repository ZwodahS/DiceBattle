#include "Message.hpp"

Message::Message(MessageType t)
    :type(t)
{
}

sf::Int32 Message::toInt(MessageType type)
{
    return type;
}

Message::MessageType Message::toType(sf::Int32 intValue)
{
    switch(intValue)
    {
        case GameStartMessage : return GameStartMessage;
        case AbilityUsedMessage : return AbilityUsedMessage;
        case ActiveTurnMessage : return ActiveTurnMessage;
        case AskForActionMessage : return AskForActionMessage;
        case DiceRolledResultMessage : return DiceRolledResultMessage;
        case NewDiceMessage : return NewDiceMessage;
        case EndTurnMessage : return EndTurnMessage;
        case EndGameMessage : return EndGameMessage;
        case SendDoneCommand : return SendDoneCommand;
        case SendRollCommand : return SendRollCommand;
        case SendUseAbilityCommand : return SendUseAbilityCommand;
    }
}

sf::Packet& operator << (sf::Packet& packet, const Message::MessageType& message)
{
    return packet << Message::toInt(message);
}
sf::Packet& operator >> (sf::Packet& packet, Message::MessageType& message)
{
    sf::Int32 tmp;
    packet >> tmp;
    message = Message::toType(tmp);
    return packet;
}

