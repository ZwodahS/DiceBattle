#ifndef _GAME_CONNECTION_MANAGER_H_
#define _GAME_CONNECTION_MANAGER_H_
#include "Connection.hpp"
#include <SFML/Network.hpp>
class Game;
class ConnectionManager
{
public:
    static const sf::Int32 InternalMessage = 1000;
    static const sf::Int32 ExternalMessage = 2000;
    ConnectionManager(Game& game);
    ~ConnectionManager();

    // The connection to the server (if any)
    Connection server;
    // The listener if you want to be the host.
    sf::TcpListener listener;
    std::vector<Connection*> _connectedClients;

    /** 
     * Try to be a host
     *  return false if already connected to a server or if the listener fails to listen.
     */
    bool host();
    /**
     * Stop the hosting if any
     */
    bool stopHost();
    /**
     * Connect to the ip
     */ 
    bool connectTo(std::string ipAddr);
    
    /**
     * This will ask the listener to listen for message
     */
    void listen();
    
    /**
     * This will ask all the conection to receive any message
     */
    void receive();
    Game& game;

    /**
     * A boolean representing if the connection is current hosting a game
     */
    bool hosting;
    /**
     * A boolean representing if the client is currently connected to a server.
     */
    bool connected;
private:
    void hostingDisconnected();
    void serverDisconnected();
    void packetReceivedFromClient(sf::Packet& packet, Connection* connection);
    void packetReceivedFromServer(sf::Packet& packet);
};
#endif
