#ifndef _GAME_LOGIC_BATTLESERVER_H_
#define _GAME_LOGIC_BATTLESERVER_H_
#include <SFML/Network.hpp>
#include "../messages/Message.hpp"
#include "../messages/g_messages.hpp"
#include <queue>
class BattleServer
{
public:
    
    BattleServer();
    ~BattleServer();

    Message* popNextMessage();
    /**
     * Forward the packet from another layer to this battle server.
     * This allow me to do a tier system for message sending/receiving like how network protocol are liked.
     * I can have another packet processor for chatting and lobby code if I want to implement them in the future.
    */
    void forwardPacket(sf::Packet& packet);    
    bool connected;
private:
    std::queue<Message*> messages;
};
#endif
