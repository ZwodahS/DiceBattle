#ifndef _GAME_LOGIC_TCPCLIENT_H_
#define _GAME_LOGIC_TCPCLIENT_H_
#include "BattlePacketLayer.hpp"
#include "../../z_framework/zf_network/Connection.hpp"
#include "../messages/g_messages.hpp"
#include "TcpViewer.hpp"
#include "GeneralUpdater.hpp"
#include <SFML/Network.hpp>
class TcpClient 
{
public:
    TcpClient(zf::Connection& connection, PlayerRole::ePlayerRole r, BattlePacketLayer& packetLayer);

    bool isConnected();
    bool isConnectedBy(zf::Connection& connection);
    void sendMessage(sf::Packet& packet);    
    void packetReceived(sf::Packet& packet);
    void appendHeader(sf::Packet& packet);
    TcpViewer viewer;
    GeneralUpdater updater;
    
    zf::Connection& connection;
    PlayerRole::ePlayerRole role;
    BattlePacketLayer& parent;

};
#endif
