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
#include "PacketProcessingLayer.hpp"
namespace zf
{
    PacketProcessingLayer::PacketProcessingLayer(PacketUpStream& up, sf::Int32 h)
        :_header(h), _upStream(up)
    {
    }
    
    PacketProcessingLayer::~PacketProcessingLayer()
    {
    }

    void PacketProcessingLayer::appendHeader(sf::Packet& packet)
    {
        // append the header from upstream.
        _upStream.appendHeader(packet);
        // append the header for this.
        packet << _header;
    }

    Connection* PacketProcessingLayer::getConnection(std::string name)
    {
        return _upStream.getConnection(name);
    }
    
    bool PacketProcessingLayer::sendPacket(std::string& name, sf::Packet& packet)
    {
        return _upStream.sendPacket(name, packet);
    }

    bool PacketProcessingLayer::sendPacketToServer(sf::Packet& packet)
    {
        return _upStream.sendPacketToServer(packet);
    }

    std::string PacketProcessingLayer::getUniqueId()
    {
        return _upStream.getUniqueId();
    }

    sf::Int32 PacketProcessingLayer::getHeader()
    {
        return _header;
    }

    void PacketProcessingLayer::packetReceived(sf::Packet& packet, Connection& connection)
    {
        sf::Int32 h;
        if(!(packet >> h))
        {
            // bad packet
            return;
        }
        // find out which downstream to send to.
        for(std::vector<PacketDownStream*>::iterator it = _downStreams.begin() ; it != _downStreams.end() ; ++it)
        {
            // check for header
            if(h == (*it)->getHeader())
            {
                // forward the message to the downstream
                (*it)->packetReceived(packet, connection);
                // messages should never be sent to more than 1 downstream
                break;
            } 
        }
    }

    void PacketProcessingLayer::packetReceivedFromServer(sf::Packet& packet)
    {
        sf::Int32 h;
        if(!(packet >> h))
        {
            // bad packet
            return;
        }
        // find out which downstream to send to.
        for(std::vector<PacketDownStream*>::iterator it = _downStreams.begin() ; it != _downStreams.end() ; ++it)
        {
            // check for header
            if(h == (*it)->getHeader())
            {
                // forward the message to the downstream
                (*it)->packetReceivedFromServer(packet);
                // messages should never be sent to more than 1 downstream
                break;
            } 
        }
    }
}
