#include "TcpViewer.hpp"
#include "TcpClient.hpp"
TcpViewer::TcpViewer(TcpClient& p, PlayerRole::ePlayerRole r)
    :_parent(p), GameViewer(r)
{
}

TcpViewer::~TcpViewer()
{
}

bool TcpViewer::isConnected()
{
    return _parent.isConnected();
}


void TcpViewer::sendMessage(DB_GameStartMessage message)
{
    sf::Packet packet;
    _parent.appendHeader(packet);
    packet << message.type << message;
    _parent.sendMessage(packet);
}
void TcpViewer::sendMessage(DB_ActiveTurnMessage message)
{
    sf::Packet packet;
    _parent.appendHeader(packet);
    packet << message.type << message;
    _parent.sendMessage(packet);
}
void TcpViewer::sendMessage(DB_AskForActionMessage message)
{
    sf::Packet packet;
    _parent.appendHeader(packet);
    packet << message.type << message;
    _parent.sendMessage(packet);
}
void TcpViewer::sendMessage(DB_AbilityUsedMessage message)
{
    sf::Packet packet;
    _parent.appendHeader(packet);
    packet << message.type << message;
    _parent.sendMessage(packet);
}
void TcpViewer::sendMessage(DB_DiceRolledResultMessage message)
{
    sf::Packet packet;
    _parent.appendHeader(packet);
    packet << message.type << message;
    _parent.sendMessage(packet);
}
void TcpViewer::sendMessage(DB_NewDiceMessage message)
{
    sf::Packet packet;
    _parent.appendHeader(packet);
    packet << message.type << message;
    _parent.sendMessage(packet);
}
void TcpViewer::sendMessage(DB_EndTurnMessage message)
{
    sf::Packet packet;
    _parent.appendHeader(packet);
    packet << message.type << message;
    _parent.sendMessage(packet);
}
void TcpViewer::sendMessage(DB_EndGameMessage message)
{
    sf::Packet packet;
    _parent.appendHeader(packet);
    packet << message.type << message;
    _parent.sendMessage(packet);
}
