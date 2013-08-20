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
#ifndef _ZF_NETWORK_PACKETPROCESSINGLAYER_H_
#define _ZF_NETWORK_PACKETPROCESSINGLAYER_H_
#include "PacketUpStream.hpp"
#include "PacketDownStream.hpp"
#include <SFML/Network.hpp>
namespace zf
{
    /**
     * This is a class for layers that just do forwarding.
     */
    class PacketProcessingLayer : public PacketUpStream , public PacketDownStream
    {
    public:
        PacketProcessingLayer(PacketUpStream& upStream, sf::Int32 header);
        virtual ~PacketProcessingLayer();

        virtual void appendHeader(sf::Packet& packet);
        virtual Connection* getConnection(std::string name);
        virtual bool sendPacket(std::string& name, sf::Packet& packet);
        virtual bool sendPacketToServer(sf::Packet& packet); 
        virtual std::string getUniqueId();


        virtual sf::Int32 getHeader();
        virtual void packetReceived(sf::Packet& packet, Connection& connection);
        virtual void packetReceivedFromServer(sf::Packet& packet);
    private:
        sf::Int32 _header;
        std::vector<PacketDownStream*> _downStreams;
        PacketUpStream& _upStream;
    };
}
#endif
