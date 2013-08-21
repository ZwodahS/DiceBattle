#include "BattleServer.hpp"
#include "BattlePacketLayer.hpp"
#include <iostream>
BattleServer::BattleServer(BattlePacketLayer& parent)
    :connected(false), _parent(parent)
{
}

BattleServer::~BattleServer()
{
}

Message* BattleServer::popNextMessage()
{
    if(messages.size() == 0)
    {
        return 0;
    }
    Message* m = messages.front();
    messages.pop();
    return m;

}

void BattleServer::packetReceivedFromServer(sf::Packet& packet)
{
    sf::Int32 typeIntValue;
    packet >> typeIntValue;
    Message::MessageType t = Message::toType(typeIntValue);
    if(t == Message::GameStartMessage)
    {
        DB_GameStartMessage* message = new DB_GameStartMessage();
        packet >> *message;
        messages.push(message);
    }
    else if (t == Message::ActiveTurnMessage)
    {
        DB_ActiveTurnMessage* message = new DB_ActiveTurnMessage();
        packet >> *message;
        messages.push(message);
    }    
    else if (t == Message:: AskForActionMessage)
    {
        DB_AskForActionMessage* message = new DB_AskForActionMessage();
        packet >> *message;
        messages.push(message);
    }
    else if (t == Message:: DiceRolledResultMessage)
    {
        DB_DiceRolledResultMessage* message = new DB_DiceRolledResultMessage();
        packet >> *message;
        messages.push(message);
    }
    else if (t == Message:: AbilityUsedMessage)
    {
        DB_AbilityUsedMessage* message = new DB_AbilityUsedMessage();
        packet >> *message;
        messages.push(message);
    }
    else if (t == Message:: NewDiceMessage)
    {
        DB_NewDiceMessage* message = new DB_NewDiceMessage();
        packet >> *message;
        messages.push(message);
    }
    else if (t == Message:: EndTurnMessage)
    {
        DB_EndTurnMessage* message = new DB_EndTurnMessage();
        packet >> *message;
        messages.push(message);
    }
    else if (t == Message:: EndGameMessage)
    {
        DB_EndGameMessage* message = new DB_EndGameMessage();
        packet >> *message;
        messages.push(message);
    }
    else if (t == Message:: SendDoneCommand)
    {
        DB_SendDoneCommand* message = new DB_SendDoneCommand();
        packet >> *message;
        messages.push(message);
    }
    else if (t == Message:: SendRollCommand)
    {
        DB_SendRollCommand* message = new DB_SendRollCommand();
        packet >> *message;
        messages.push(message);
    }
    else if (t == Message:: SendUseAbilityCommand)
    {
        DB_SendUseAbilityCommand* message = new DB_SendUseAbilityCommand();
        packet >> *message;
        messages.push(message);
    }
}

void BattleServer::sendPacketToServer(sf::Packet& packet)
{
    _parent.sendPacketToServer(packet);
}

void BattleServer::appendHeader(sf::Packet& packet)
{
    _parent.appendHeader(packet);
}
