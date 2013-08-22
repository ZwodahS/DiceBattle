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
#ifndef _ZF_NETWORK_CONNECTION_H_
#define _ZF_NETWORK_CONNECTION_H_
#include <SFML/Network.hpp>
namespace zf
{
    /**
     * Defines a single connection that is connected to this server.
     * It stores a unique identifier to identifier this connection.
     * The unique identifier can be used as a username.
     */
    class Connection
    {
    public:
        /**
         * If managed is true, the tcpSocket will be disconnected and freed when the connection object is removed.
         */
        Connection(bool managed = true);
        ~Connection();
        /**
         * The name of this connection
         */
        std::string name;
        /**
         * bool representing if this connection is verified.
         */
        bool verified;
        /**
         * The socket that this connection is connected by.
         */
        sf::TcpSocket* socket;
        /**
         * Send the packet to this socket.
         */
        sf::Socket::Status sendPacket(sf::Packet& packet);
    private:
        // prevent copy and assign
        Connection(const Connection& conn);
        Connection& operator=(const Connection& conn);
        bool _managed;
    };
}
#endif
