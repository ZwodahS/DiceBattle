#ifndef _GAME_LOGIC_BATTLEPACKETLAYER_H_
#define _GAME_LOGIC_BATTLEPACKETLAYER_H_
#include "../constants/PlayerRole.hpp"
#include "../../z_framework/zf_network/PacketUpStream.hpp"
#include "../../z_framework/zf_network/PacketDownStream.hpp"
#include "../../z_framework/zf_network/ConnectionListener.hpp"
/**
 * Defines the layer that passes the message around to the correct places. 
 */
class TcpClient;
class BattleServer;
class BattlePacketLayer : public zf::PacketDownStream, public zf::ConnectionListener
{
public:
    // packet up stream methods
    virtual void appendHeader(sf::Packet& packet);
    virtual zf::Connection* getConnection(std::string name);
    virtual bool sendPacket(std::string& name, sf::Packet& packet);
    virtual bool sendPacketToServer(sf::Packet& packet);
    virtual std::string getUniqueId();
    // down stream virtual methods.
    virtual sf::Int32 getHeader();
    virtual void packetReceived(sf::Packet& packet, zf::Connection& connection);
    virtual void packetReceivedFromServer(sf::Packet& packet);
    // Connection Listener virtual methods
    // I actually only needs to deal with client disconnected here.
    virtual void clientConnected(zf::Connection* connection);
    virtual void clientDisconnected(zf::Connection* connection);
    virtual void serverStarted();
    virtual void serverStopped();
    virtual void serverConnected();
    virtual void serverDisconnected();
    virtual void nameInUsed();
    virtual void nameVerified(std::string name);
    virtual void clientVerified(zf::Connection* connection);


    // get a viewer from a connection
    // If the viewer do not exist, a new 1 will be created and return 
    TcpClient& getClient(zf::Connection& connection, PlayerRole::ePlayerRole r);
    void removeClient(zf::Connection& connection);
    void setBattleServer(BattleServer* battleServer);
    void resetLayer();
    BattlePacketLayer(zf::PacketUpStream& upstream);
private:
    std::vector<TcpClient*> _viewers;
    BattleServer* _battleServer;
    zf::PacketUpStream& _upstream;
};
#endif
