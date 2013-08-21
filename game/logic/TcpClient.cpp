#include "TcpClient.hpp"
#include "../messages/Message.hpp"
TcpClient::TcpClient(zf::Connection& c, PlayerRole::ePlayerRole r, BattlePacketLayer& packetLayer)
    :connection(c), role(r), parent(packetLayer), viewer(*this, r), updater(r)
{
}

bool TcpClient::isConnected()
{
}

bool TcpClient::isConnectedBy(zf::Connection& c)
{
    return &connection == &c;
}

void TcpClient::appendHeader(sf::Packet& packet)
{
    parent.appendHeader(packet);
}

void TcpClient::sendMessage(sf::Packet& packet)
{
    parent.sendPacket(connection.name, packet);
}

void TcpClient::packetReceived(sf::Packet& packet)
{
    // when i receive a packet, it will be from a "updater" in the client.
    // In that case I need to convert the packet into the message and put it in the general updater.
    Message::MessageType type;
    packet >> type;
    if(type == Message::SendDoneCommand)
    {
        DB_SendDoneCommand* message = new DB_SendDoneCommand();
        packet >> *message;
        updater.pushMessage(message);
    }
    else if(type == Message::SendRollCommand)
    {
        DB_SendRollCommand* message = new DB_SendRollCommand();
        packet >> *message;
        updater.pushMessage(message);
    }
    else if(type == Message::SendUseAbilityCommand)
    {
        DB_SendUseAbilityCommand* message = new DB_SendUseAbilityCommand();
        packet >> *message;
        updater.pushMessage(message);
    }
}
