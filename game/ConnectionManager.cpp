#include "ConnectionManager.hpp"
#include "Game.hpp"
#define PORT 37890
ConnectionManager::ConnectionManager(Game& g)
    :game(g), hosting(false), connected(false)
{
    server.name = "Server";
}

ConnectionManager::~ConnectionManager()
{
}

bool ConnectionManager::host()
{
    if(hosting)
    {
        return false;
    }
    else 
    {
        sf::Socket::Status status = listener.listen(PORT);
        if(status == sf::Socket::Done)
        {
            hosting = true;
            game.hostingStarted();
            listener.setBlocking(false);
        }
        else if(status == sf::Socket::NotReady)
        {
            hosting = false;
        }
        else if(status == sf::Socket::Disconnected)
        {
            hosting = false;
        }
        else
        {
            // error
            hosting = false;
        }
        return hosting;
    }
}

bool ConnectionManager::stopHost()
{
    if(hosting)
    {
        hostingDisconnected();
    }
    return !hosting;
}

void ConnectionManager::hostingDisconnected()
{
    // disconnect all the client
    for(std::vector<Connection*>::iterator it = _connectedClients.begin() ; it != _connectedClients.end() ; ++it)
    {
        (*it)->socket.disconnect(); 
        delete *it;
    }
    // close the listener
    listener.close();
    // remove all the pointers
    _connectedClients.clear();
    hosting = false;
    game.hostingStopped();
}
bool ConnectionManager::connectTo(std::string ip)
{
    if(hosting)
    {
        return false;
    }
    else if(connected)
    {
        server.socket.disconnect();
        game.serverDisconnected();
    }
    connected = false;
    std::cout << ip << std::endl;
    sf::Socket::Status status = server.socket.connect(ip, PORT);
    if(status == sf::Socket::Done)
    {
        std::cout << "ConnectionManager.cpp : 86 " << std::endl;
        server.socket.setBlocking(false);
        connected = true;
        game.serverConnected();
    }
    else if(status == sf::Socket::NotReady)
    {
        //not ready
    }
    else if(status == sf::Socket::Disconnected)
    {
    }
    else
    {
    }
    return connected;
}

void ConnectionManager::listen()
{
    // if this connection is not hosting then don't bother listening
    if(hosting)
    {
        Connection* connection = new Connection();
        sf::Socket::Status status = listener.accept(connection->socket);
        if(status == sf::Socket::Done)
        {
            connection->socket.setBlocking(false);
            game.clientConnected(connection);
            _connectedClients.push_back(connection);
        }
        else if(status == sf::Socket::NotReady)
        {
        }
        else if(status == sf::Socket::Disconnected)
        {
            hostingDisconnected();
        }
        else
        {
            hostingDisconnected();
        }
    }
}

void ConnectionManager::receive()
{
    if(hosting)
    {
        for(std::vector<Connection*>::iterator it = _connectedClients.begin() ; it != _connectedClients.end() ;)
        {
            sf::Packet packet;
            sf::Socket::Status status = (*it)->socket.receive(packet); 
            if(status == sf::Socket::Done)
            {
                // a packet is received.
                packetReceivedFromClient(packet, *it);
            }
            else if(status == sf::Socket::NotReady)
            {
                // no packet
            }
            else if(status == sf::Socket::Disconnected)
            {
                game.clientDisconnected(*it);
                delete *it;
                it = _connectedClients.erase(it);
                continue;
            }
            else
            {
                game.clientDisconnected(*it);
                delete *it;
                it = _connectedClients.erase(it);
                continue;
            }
            ++it;
        }
    }
    if(connected)
    {
        // read from server
        sf::Packet packet;
        sf::Socket::Status status = server.socket.receive(packet); 
        if(status == sf::Socket::Done)
        {
            // a packet is received.
            packetReceivedFromServer(packet);
        }
        else if(status == sf::Socket::NotReady)
        {
            // no packet
        }
        else if(status == sf::Socket::Disconnected)
        {
            serverDisconnected();
        }
        else
        {
            serverDisconnected();
        }
    }
}

void ConnectionManager::serverDisconnected()
{
    server.socket.disconnect();
    connected = false;
    game.serverDisconnected();
}

void ConnectionManager::packetReceivedFromClient(sf::Packet& packet, Connection* connection)
{
    sf::Int32 messageType; 
    packet >> messageType;
    if(messageType == InternalMessage)
    {
        // just in case i need something
    }
    else
    {
        game.packetReceived(packet, connection);
    }
}

void ConnectionManager::packetReceivedFromServer(sf::Packet& packet)
{
    sf::Int32 messageType; 
    packet >> messageType;
    if(messageType == InternalMessage)
    {
        // just in case i need something
    }
    else 
    {
        game.packetReceivedFromServer(packet);
    }
}

void ConnectionManager::appendExternalMessageHeader(sf::Packet& packet)
{
    packet << ExternalMessage;
}
