#include "TcpViewer.hpp"

TcpViewer::TcpViewer(sf::Int32 prefix, sf::TcpSocket& c, PlayerRole::ePlayerRole r)
    :GameViewer(r), connected(false), header(prefix), connection(&c)
{
}

TcpViewer::~TcpViewer()
{
}

bool TcpViewer::isConnected()
{
    return connected && connection != 0;
}
void TcpViewer::sendMessage(DB_GameStartMessage message)
{
    if(connection != 0 && connected)
    {
        sf::Packet packet;
        packet << header << message.type << message;
        sf::Socket::Status status = connection->send(packet);
        if(status == sf::Socket::Done)
        {
            // sent
        }
        else if(status == sf::Socket::Disconnected)
        {
            connected = false;
        }
    }
}
void TcpViewer::sendMessage(DB_ActiveTurnMessage message)
{
    if(connection != 0 && connected)
    {
        sf::Packet packet;
        packet << header << message.type << message;
        sf::Socket::Status status = connection->send(packet);
        if(status == sf::Socket::Done)
        {
            // sent
        }
        else if(status == sf::Socket::Disconnected)
        {
            connected = false;
        }
    }
}
void TcpViewer::sendMessage(DB_AskForActionMessage message)
{
    if(connection != 0 && connected)
    {
        sf::Packet packet;
        packet << header << message.type << message;
        sf::Socket::Status status = connection->send(packet);
        if(status == sf::Socket::Done)
        {
            // sent
        }
        else if(status == sf::Socket::Disconnected)
        {
            connected = false;
        }
    }
}
void TcpViewer::sendMessage(DB_AbilityUsedMessage message)
{
    if(connection != 0 && connected)
    {
        sf::Packet packet;
        packet << header << message.type << message;
        sf::Socket::Status status = connection->send(packet);
        if(status == sf::Socket::Done)
        {
            // sent
        }
        else if(status == sf::Socket::Disconnected)
        {
            connected = false;
        }
    }
}
void TcpViewer::sendMessage(DB_DiceRolledResultMessage message)
{
    if(connection != 0 && connected)
    {
        sf::Packet packet;
        packet << header << message.type << message;
        sf::Socket::Status status = connection->send(packet);
        if(status == sf::Socket::Done)
        {
            // sent
        }
        else if(status == sf::Socket::Disconnected)
        {
            connected = false;
        }
    }
}
void TcpViewer::sendMessage(DB_NewDiceMessage message)
{
    if(connection != 0 && connected)
    {
        sf::Packet packet;
        packet << header << message.type << message;
        sf::Socket::Status status = connection->send(packet);
        if(status == sf::Socket::Done)
        {
            // sent
        }
        else if(status == sf::Socket::Disconnected)
        {
            connected = false;
        }
    }
}
void TcpViewer::sendMessage(DB_EndTurnMessage message)
{
    if(connection != 0 && connected)
    {
        sf::Packet packet;
        packet << header << message.type << message;
        sf::Socket::Status status = connection->send(packet);
        if(status == sf::Socket::Done)
        {
            // sent
        }
        else if(status == sf::Socket::Disconnected)
        {
            connected = false;
        }
    }
}
void TcpViewer::sendMessage(DB_EndGameMessage message)
{
    if(connection != 0 && connected)
    {
        sf::Packet packet;
        packet << header << message.type << message;
        sf::Socket::Status status = connection->send(packet);
        if(status == sf::Socket::Done)
        {
            // sent
        }
        else if(status == sf::Socket::Disconnected)
        {
            connected = false;
        }
    }
}
