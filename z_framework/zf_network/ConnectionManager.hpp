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
#ifndef _ZF_ZFNETWORK_CONNECTIONMANAGER_H_
#define _ZF_ZFNETWORK_CONNECTIONMANAGER_H_
#include "Connection.hpp"
#include "PacketUpStream.hpp"
#include <SFML/Network.hpp>
namespace zf
{
    /**
     * ConnectionManager provides the methods and functions to handle connecting and hosting.
     * It will provide functions for reconnecting (hopefully) in the future.
     *
     */
    class PacketDownStream;
    class ConnectionListener;
    class ConnectionManager : public PacketUpStream
    {
    public:
        ConnectionManager();
        ~ConnectionManager();
        bool isConnected();
        bool isHosting();
        /**
         * Start a server.
         * If this is already connected to a server, it will return false.
         */
        bool startServer(unsigned short port);
        /**
         * Stop the server.
         * It will disconnect all connected clients and free all of the connection resources.
         */
        void stopServer();
        /**
         * Connect to a server.
         * return false if this is already connected to a server or if this is a server.
         */
        bool connectTo(std::string ipAddr, unsigned short port);
        /**
         * Disconnect from server.
         * return false if this is not connected.
         */
        void disconnect();
        /**
         * Override PacketUpstream methods
         */
        void appendHeader(sf::Packet& packet);
        /**
         * Get a connection
         */        
        Connection* getConnection(std::string name);
        virtual bool sendPacket(std::string& name, sf::Packet& packet);
        virtual bool sendPacketToServer(sf::Packet& packet);
        virtual std::string getUniqueId();
        /**
         * Listen for connections
         */
        void listen();
        /**
         * Listen for messages
         */
        void receive();

        void addListener(ConnectionListener& listener);
        void removeListener(ConnectionListener& listener);

        std::string verifiedName;


        void addDownStream(PacketDownStream& downStream);
        void removeDownStream(PacketDownStream& downStream);
    private:
        
        /**
         * There are 2 types of messages that connection manager needs to care about
         * Internal Messages are used internal to send verification messages etc.
         *    Server to Client 
         *      1. NameInUsedMessage - Send to client to tell them that their unique identifier is in used
         *      2. NameVerified - Send to client to tell them that they are verified with a particular name
         *    Client to Server
         *      1. VerifyName - Send to server to verify this client with a name
         *      2. VerifyRandom - Ask Server to give this client a random name // TODO
         */
        static const sf::Int32 InternalMessage = 1000;
        static const sf::Int32 ExternalMessage = 2000;

        /// Internal message type code
        static const sf::Int32 NameInUsedMessage = 1001;
        static const sf::Int32 NameVerifiedMessage = 1002;
        static const sf::Int32 VerifyNameMessage = 1101;

        bool _isHosting;
        bool _isConnected;
        /*
         * Stores the list of clients if this is the server.
         */
        std::vector<Connection*> _connectedClients;
        /**
         * Stores the list of downstreams
         */
        std::vector<PacketDownStream*> _downstreams;
        /**
         * Server listener.
         */
        sf::TcpListener _listener;
        std::vector<ConnectionListener*> _connectionListeners;   

        /**
         * If you are connected to a server, this stores the socket for the server.
         */
        sf::TcpSocket _serverSocket;
        /**
         * Boolean representing if you are verified with the server.
         * Only verified client will be able to received/send message outside of ConnectionManager
         */
        bool _verified;

        ////////////////////////// Internal message ///////////////////////////
        void processUnverifiedPacket(sf::Packet& packet, Connection* connection);
        void processVerifiedPacket(sf::Packet& packet, Connection* connection);
        void processServerPacket(sf::Packet& packet);

        void processClientConnected(Connection* connection);
        void processClientDisconnected(Connection* connection);
        void processServerStarted();
        void processServerStopped();
        void processServerConnected();
        void processServerDisconnected();

        void processInternalMessage(sf::Packet& packet, Connection* connection);
        void processServerInternalMessage(sf::Packet& packet);

        bool sendNameInUseMessage(Connection* connection);
        bool sendNameVerifiedMessage(Connection* connection, std::string name);

        bool sendVerifyNameMessage(std::string name);
        bool sendPacket(Connection& connection, sf::Packet& packet);
    };
}
#endif
