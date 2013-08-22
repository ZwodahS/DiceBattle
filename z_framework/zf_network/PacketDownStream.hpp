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
#ifndef _ZF_NETWORK_PACKETDOWNSTREAM_H_
#define _ZF_NETWORK_PACKETDOWNSTREAM_H_
#include <SFML/Network.hpp>
namespace zf
{
    /**
     * Defines the abstract interface class where packets is sent to after they are received.
     * Every downstream must belong to one upstream.
     */
    class Connection;
    class PacketDownStream
    {
    public:
        /**
         * Get the header data for this downstream.
         */
        virtual sf::Int32 getHeader() = 0;
        /**
         * Packet is received from this connection.
         */
        virtual void packetReceived(sf::Packet& packet, Connection& connection) = 0;
        /**
         * Packet is received from server.
         */
        virtual void packetReceivedFromServer(sf::Packet& packet) = 0;
    protected:
    };
}
#endif
