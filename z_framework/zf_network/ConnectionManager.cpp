/*
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 * 
 * Copyright (C) 2013 ZwodahS(ericnjf@gmail.com) 
 * zwodahs.wordpress.com
 * 
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 * 
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 
 *  0. You just DO WHAT THE **** YOU WANT TO.
 * 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. 
 */
#include "ConnectionManager.hpp"
#include "PacketDownStream.hpp"
#include "ConnectionListener.hpp"
#include <iostream>
namespace zf
{
    ConnectionManager::ConnectionManager()
        :_isHosting(false), _isConnected(false), _verified(false)
    {
    }

    ConnectionManager::~ConnectionManager()
    {
    }

    bool ConnectionManager::isConnected()
    {
        return _isConnected;
    }

    bool ConnectionManager::isHosting()
    {
        return _isHosting;
    }

    bool ConnectionManager::startServer(unsigned short port)
    {
        if(_isHosting || _isConnected)
        {
            return false;
        }
        else 
        {
            sf::Socket::Status status = _listener.listen(port);
            if(status == sf::Socket::Done)
            {
                _isHosting = true;
                _listener.setBlocking(false);
                processServerStarted();
            }
            else if(status == sf::Socket::NotReady)
            {
                _isHosting = false;
            }
            else if(status == sf::Socket::Disconnected)
            {
                _isHosting = false;
            }
            else
            {
                _isHosting = false;
            }
            return _isHosting;
        }
    }

    void ConnectionManager::stopServer()
    {
        if(_isHosting)
        {
            for(std::vector<Connection*>::iterator it = _connectedClients.begin() ; it != _connectedClients.end() ; ++it)
            {
                processClientDisconnected(*it);
                if((*it)->socket != 0)
                {
                    (*it)->socket->disconnect(); 
                }
                delete *it;
            }
            _listener.close();
            _connectedClients.clear();
            _isHosting = false;
            processServerStopped();
        }
    }

    bool ConnectionManager::connectTo(std::string ip, unsigned short port)
    {
        if(_isHosting || _isConnected)
        {
            return false;
        }
        sf::Socket::Status status = _serverSocket.connect(ip, port);
        if(status == sf::Socket::Done)
        {
            _serverSocket.setBlocking(false);
            _isConnected = true;
            processServerConnected();
            // send the verify name message
            sendVerifyNameMessage(verifiedName);
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
        return _isConnected;
    }


    void ConnectionManager::listen()
    {
        // if this connection is not hosting then don't bother listening
        if(_isHosting)
        {
            sf::TcpSocket* socket = new sf::TcpSocket();
            sf::Socket::Status status = _listener.accept(*socket);
            if(status == sf::Socket::Done)
            {
                socket->setBlocking(false);
                Connection* connection = new Connection(true);
                connection->socket = socket;
                processClientConnected(connection);
            }
            else if(status == sf::Socket::NotReady)
            {
                delete socket;
            }
            else if(status == sf::Socket::Disconnected)
            {
                stopServer();
                delete socket;
            }
            else
            {
                stopServer();
                delete socket;
            }
            // clean up in case there is a connection that is already disconnected
            for(std::vector<Connection*>::iterator it = _connectedClients.begin() ; it != _connectedClients.end() ; )
            {    
                if((*it)->socket == 0)
                {
                    delete (*it);
                    it = _connectedClients.erase(it);
                    continue;
                }
                ++it;
            }
        }
    }

    void ConnectionManager::disconnect()
    {
        if(_isConnected)
        {
            processServerDisconnected();
        }
    }

    void ConnectionManager::receive()
    {
        if(_isHosting)
        {
            //if is host then read from all client
            // read from the unverified client
            for(std::vector<Connection*>::iterator it = _connectedClients.begin() ; it != _connectedClients.end() ; ++it)
            {
                sf::Packet packet;
                // check for packet.
                sf::Socket::Status status = (*it)->socket->receive(packet);
                if(status == sf::Socket::Done)
                {
                    if((*it)->verified)
                    {
                        processVerifiedPacket(packet, *it);
                    }
                    else
                    {
                        processUnverifiedPacket(packet, *it);
                    }
                } 
                else if(status == sf::Socket::NotReady)
                {
                }
                else if(status == sf::Socket::Disconnected)
                {
                    // client disconnected ...
                    processClientDisconnected(*it);
                }
                else // if(status == sf::Socket::Error)
                {
                }
            }
        }
        else if(_isConnected)
        {
            sf::Packet packet;
            sf::Socket::Status status = _serverSocket.receive(packet);
            if(status == sf::Socket::Done)
            {
                processServerPacket(packet);
            }
            else if(status == sf::Socket::NotReady)
            {
            }
            else if(status == sf::Socket::Disconnected)
            {
                // server disconnected ... 
                processServerDisconnected();
            }
        }
    }

    void ConnectionManager::appendHeader(sf::Packet& packet)
    {
        packet << ExternalMessage;
    }
    
    Connection* ConnectionManager::getConnection(std::string name)
    {
        for(std::vector<Connection*>::iterator it = _connectedClients.begin() ; it != _connectedClients.end() ; ++it)
        {
            if((*it)->verified && (*it)->name == name)
            {
                return *it;
            } 
        }
        return 0;
    }

    void ConnectionManager::processUnverifiedPacket(sf::Packet& packet, Connection* connection)
    {
        sf::Int32 type;
        packet >> type;
        if(type == InternalMessage)
        {
            processInternalMessage(packet, connection);
        }
        else
        {
            // Unverified will not be forward down.
        }
    }
    void ConnectionManager::processVerifiedPacket(sf::Packet& packet, Connection* connection)
    {
        sf::Int32 type;
        packet >> type;
        if(type == InternalMessage)
        {
            processInternalMessage(packet, connection);
        }
        else
        {
            // search for the down stream to push to.
            if(packet >> type)
            {
                for(std::vector<PacketDownStream*>::iterator it = _downstreams.begin() ; it != _downstreams.end() ; ++it)
                {
                    if((*it)->getHeader() == type)
                    {
                        (*it)->packetReceived(packet, *connection); 
                    }
                }
            }
        }
    }

    void ConnectionManager::processServerPacket(sf::Packet& packet)
    {
        sf::Int32 type;
        packet >> type;
        if(type == InternalMessage)
        {
            processServerInternalMessage(packet);
        }
        else 
        {
            if(!_verified)
            {
                // if not verified, cannot pass to downstream
            } 
            else 
            {
                if(packet >> type)
                {
                    for(std::vector<PacketDownStream*>::iterator it = _downstreams.begin() ; it != _downstreams.end() ; ++it)
                    {
                        if((*it)->getHeader() == type)
                        {
                            (*it)->packetReceivedFromServer(packet); 
                            break;
                        }
                    }
                }
            }
        }
    }

    void ConnectionManager::processClientConnected(Connection* connection)
    {
        for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; ++it)
        {
            (*it)->clientConnected(connection); 
        }
        _connectedClients.push_back(connection);
    }
    void ConnectionManager::processClientDisconnected(Connection* connection)
    {
        for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; ++it)
        {
            (*it)->clientDisconnected(connection); 
        }
        // find out where the connection is at.
        connection->socket->disconnect();
        delete connection->socket;
        connection->socket = 0;
        // I don't really want to delete the connection here, as this might be part of a loop
    }

    void ConnectionManager::processServerStarted()
    {
        for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; ++it)
        {
            (*it)->serverStarted();    
        }
    }
    void ConnectionManager::processServerStopped()
    {
        for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; ++it)
        {
            (*it)->serverStopped(); 
        }
    }
    void ConnectionManager::processServerConnected()
    {
        for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; ++it)
        {
            (*it)->serverConnected(); 
        }
    }
    void ConnectionManager::processServerDisconnected()
    {
        for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; ++it)
        {
            (*it)->serverDisconnected(); 
        }
        _serverSocket.disconnect();
        _isConnected = false;
    }

    void ConnectionManager::addListener(ConnectionListener& l)
    {
        this->_connectionListeners.push_back(&l);
    }

    void ConnectionManager::removeListener(ConnectionListener& l)
    {
        for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; )
        {    
            if(&l == *it)
            {
                it = _connectionListeners.erase(it);
                continue;
            }
            ++it;
        }
    }

    // This is for if this is a host and this message is received from a client.

    void ConnectionManager::processInternalMessage(sf::Packet& packet, Connection* connection)
    {
        sf::Int32 type;
        if(packet >> type)
        {
            if(type == VerifyNameMessage)
            {
                // make sure that this client is not yet verified.
                std::string name;
                if(packet >> name)
                {
                    bool nameUsed = false;
                    for(std::vector<Connection*>::iterator it = _connectedClients.begin() ; it != _connectedClients.end() ; ++it)
                    {
                        if((*it)->socket != 0 && (*it)->verified && (*it)->name == name)
                        {
                            nameUsed = true;
                            break;
                        }
                    }
                    if(nameUsed)
                    {
                        sendNameInUseMessage(connection);
                    }
                    else
                    {
                        connection->name = name;
                        connection->verified = true;
                        if(sendNameVerifiedMessage(connection, name))
                        {
                            for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; ++it)
                            {
                                (*it)->clientVerified(connection); 
                            }
                        }
                    }
                }
            }
        }
    }

    // this is for messages received from server
    void ConnectionManager::processServerInternalMessage(sf::Packet& packet)
    {
        sf::Int32 type;
        if(packet >> type)
        {
            if(type == NameInUsedMessage)
            {
                // for this, i do nothing except inform all connectionListener 
                for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; ++it)
                {
                    (*it)->nameInUsed(); 
                }
            }
            else if(type == NameVerifiedMessage)
            {
                // get the name assigned to us.
                std::string name;
                if(packet >> name)
                {
                    // set the verified to true and set our verified name
                    this->_verified = true;
                    this->verifiedName = name;
                    // inform all listener.
                    for(std::vector<ConnectionListener*>::iterator it = _connectionListeners.begin() ; it != _connectionListeners.end() ; ++it)
                    {
                        (*it)->nameVerified(name);
                    }
                }
            }
        }
    }

    /** 
     * Send the NameInUsedMessage to a client
     */
    bool ConnectionManager::sendNameInUseMessage(Connection* connection)
    {
        sf::Packet packet;
        packet << InternalMessage << NameInUsedMessage;
        if(connection != 0)
        {
            return sendPacket(*connection, packet);
        }
    }

    bool ConnectionManager::sendNameVerifiedMessage(Connection* connection, std::string name)
    {
        sf::Packet packet;
        packet << InternalMessage << NameVerifiedMessage << name;
        if(connection != 0)
        {
            return sendPacket(*connection, packet);
        }
    }

    // send to the server to verify this client's name
    bool ConnectionManager::sendVerifyNameMessage(std::string name)
    {
        if(!_isConnected)
        {
            return false;
        }
        sf::Packet packet;
        packet << InternalMessage << VerifyNameMessage << name;
        return sendPacketToServer(packet);
    }

    bool ConnectionManager::sendPacket(std::string& name, sf::Packet& packet)
    {
        if(_isHosting)
        {
            Connection* conn = getConnection(name);
            if(conn != 0)
            {
                return sendPacket(*conn, packet);
            }
        }
    }

    bool ConnectionManager::sendPacket(Connection& connection, sf::Packet& packet)
    {
        sf::Socket::Status status = connection.sendPacket(packet);
        if(status == sf::Socket::Done)
        {
            // do nothing
            return true;
        }
        else if(status == sf::Socket::NotReady)
        {
            return false;
        }
        else if(status == sf::Socket::Disconnected)
        {
            processClientDisconnected(&connection);
            return false;
        }
        else // if(status == sf::Status::Error)
        {
            processClientDisconnected(&connection);
            return false;
        }
    }

    bool ConnectionManager::sendPacketToServer(sf::Packet& packet)
    {
        if(_isConnected)
        {
            sf::Socket::Status status = _serverSocket.send(packet);
            if(status == sf::Socket::Done)
            {
                // do nothing
                return true;
            }
            else if(status == sf::Socket::NotReady)
            {
                return false;
            }
            else if(status == sf::Socket::Disconnected)
            {
                processServerDisconnected();
                return false;
            }
            else // if(status == sf::Status::Error)
            {
                processServerDisconnected();
                return false;
            }
        } 
    }

    std::string ConnectionManager::getUniqueId()
    {
        return verifiedName;
    }

    void ConnectionManager::addDownStream(PacketDownStream& down)
    {
        _downstreams.push_back(&down);
    }

    void ConnectionManager::removeDownStream(PacketDownStream& down)
    {
        for(std::vector<PacketDownStream*>::iterator it = _downstreams.begin() ; it != _downstreams.end() ; )
        {    
            if(&down == *it)
            {
                it = _downstreams.erase(it);
                continue;
            }
            ++it;
        }
    }
}
