#include "BattlePacketLayer.hpp"
#include "BattleServer.hpp"
#include "TcpClient.hpp"
#include <iostream>
BattlePacketLayer::BattlePacketLayer(zf::PacketUpStream& upstream)
    :_upstream(upstream), _battleServer(0)
{
}

void BattlePacketLayer::appendHeader(sf::Packet& packet)
{
    _upstream.appendHeader(packet);
    packet << getHeader();
}

zf::Connection* BattlePacketLayer::getConnection(std::string name)
{
    return _upstream.getConnection(name);
}
sf::Int32 BattlePacketLayer::getHeader()
{
    // this MUST be the same as the Battle server.
    return 9876;
}

bool BattlePacketLayer::sendPacket(std::string& name, sf::Packet& packet)
{
    return _upstream.sendPacket(name, packet);
}

bool BattlePacketLayer::sendPacketToServer(sf::Packet& packet)
{
    return _upstream.sendPacketToServer(packet);
}

std::string BattlePacketLayer::getUniqueId()
{
    return _upstream.getUniqueId();
}

void BattlePacketLayer::packetReceived(sf::Packet& packet, zf::Connection& connection)
{
    for(std::vector<TcpClient*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it)
    {
        if((*it)->isConnectedBy(connection))
        {
            (*it)->packetReceived(packet);
        } 
    }
}
void BattlePacketLayer::packetReceivedFromServer(sf::Packet& packet)
{
    if(_battleServer != 0)
    {
        _battleServer->packetReceivedFromServer(packet);
    }
}
void BattlePacketLayer::clientConnected(zf::Connection* connection)
{
}
void BattlePacketLayer::clientDisconnected(zf::Connection* connection)
{
}
void BattlePacketLayer::serverStarted()
{
}
void BattlePacketLayer::serverStopped()
{
}
void BattlePacketLayer::serverConnected()
{
}
void BattlePacketLayer::serverDisconnected()
{
}
void BattlePacketLayer::nameInUsed()
{
}
void BattlePacketLayer::nameVerified(std::string name)
{
}
void BattlePacketLayer::clientVerified(zf::Connection* connection)
{
}

TcpClient& BattlePacketLayer::getClient(zf::Connection& connection, PlayerRole::ePlayerRole r)
{
    TcpClient* client = new TcpClient(connection, r, *this);
    _viewers.push_back(client);
    return *client;
}

void BattlePacketLayer::removeClient(zf::Connection& connection)
{
    for(std::vector<TcpClient*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it)
    {
        if(&(*it)->connection == &connection)
        {
            TcpClient* client = (*it);
            _viewers.erase(it);
            delete client;
            break;
        }
    }
}

void BattlePacketLayer::setBattleServer(BattleServer* battleServer)
{
    this->_battleServer = battleServer;
}

/**
 * This method is called after every game to clean up all the server, listener and updater.
 */
void BattlePacketLayer::resetLayer()
{
    if(_battleServer != 0)
    {
        delete _battleServer;
        _battleServer = 0;
    }
    for(std::vector<TcpClient*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it)
    {
        delete *it;
    }
    _viewers.clear();
}

