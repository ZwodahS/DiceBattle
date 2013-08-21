#ifndef _GAME_LOGIC_BATTLESERVER_H_
#define _GAME_LOGIC_BATTLESERVER_H_
#include <SFML/Network.hpp>
#include "../messages/Message.hpp"
#include "../messages/g_messages.hpp"
#include "../../z_framework/zf_network/PacketUpStream.hpp"
#include "../../z_framework/zf_network/PacketDownStream.hpp"
#include "../../z_framework/zf_network/ConnectionListener.hpp"
#include "../../z_framework/zf_network/Connection.hpp"
#include <queue>
class BattlePacketLayer;
class BattleServer
{
public:
    
    BattleServer(BattlePacketLayer& parent);
    ~BattleServer();
    bool connected;
    Message* popNextMessage();
    /**
     * Forward the packet from another layer to this battle server.
     * This allow me to do a tier system for message sending/receiving like how network protocol are liked.
     * I can have another packet processor for chatting and lobby code if I want to implement them in the future.
    */
    virtual void packetReceivedFromServer(sf::Packet& packet);
    virtual void appendHeader(sf::Packet& packet);
    virtual void sendPacketToServer(sf::Packet& packet);
private:
    std::queue<Message*> messages;
    BattlePacketLayer& _parent;
};
#endif
