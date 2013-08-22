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
#ifndef _ZF_NETWORK_PACKETUPSTREAM_H_
#define _ZF_NETWORK_PACKETUPSTREAM_H_
#include <SFML/Network.hpp>
#include <string>
namespace zf
{
    class PacketDownStream;
    class Connection;
    /**
     * Defines an upstream. This allow you to wrap the packet.
     */
    class PacketUpStream
    {
    public:
        /**
         * Append the header information to the packet.
         */
        virtual void appendHeader(sf::Packet& packet) = 0;
        /**
         * Get the connection with this name.
         * return 0 if the name don't exist.
         */
        virtual Connection* getConnection(std::string name) = 0;
        /**
         * send the packet to the connection with the name
         */
        virtual bool sendPacket(std::string& name, sf::Packet& packet) = 0;
        /**
         * send the packet to the server.
         */
        virtual bool sendPacketToServer(sf::Packet& packet) = 0;
        /**
         * get the uniqueId representing the local connection manager.
         */
        virtual std::string getUniqueId() = 0;
        /**
         * method to remove the down stream. 
         */
        virtual void removeDownStream(PacketDownStream& downStream) = 0;
    };
}
#endif
