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
#include "GameSetup.hpp"
#include "../Connection.hpp"
#include <iostream>
namespace zf
{
    GameSetup::GameSetup(std::string lN, PacketUpStream& up, sf::Int32 header, bool hosting)
        :localName(lN), upstream(up), _header(header), _isHosting(hosting)
    {
    }
    GameSetup::~GameSetup()
    {
    }

    void GameSetup::appendHeader(sf::Packet& packet)
    {
        upstream.appendHeader(packet);
        packet << _header;
    }

    sf::Int32 GameSetup::getHeader()
    {
        return _header;
    }

    Connection* GameSetup::getConnection(std::string name)
    {
        return upstream.getConnection(name);
    }
    bool GameSetup::sendPacket(std::string& name, sf::Packet& packet)
    {
        return upstream.sendPacket(name, packet);
    }
    bool GameSetup::sendPacketToServer(sf::Packet& packet)
    {
        return upstream.sendPacketToServer(packet);
    }

    std::string GameSetup::getUniqueId()
    {
        return upstream.getUniqueId();
    }

    bool GameSetup::isHosting()
    {
        return _isHosting;
    }
    // message received from client.
    void GameSetup::packetReceived(sf::Packet& packet, Connection& connection)
    {
        sf::Int32 type;
        if(packet >> type)
        {
            if(type == AttemptJoinGameMessage)
            {
                processAttemptToJoinGameMessage(packet, connection);
            }
            else if(type == LeaveGameMessage)
            {
                processLeaveGameMessage(packet, connection);
            }
            else if(type == SwitchRoleMessage)
            {
                processSwitchRoleMessage(packet, connection);
            }
        }
    }
    // message received from server
    void GameSetup::packetReceivedFromServer(sf::Packet& packet)
    {
        sf::Int32 type;
        if(packet >> type)
        {
            if(type == JoinGameSuccessMessage)
            {
                processJoinGameSuccessMessage(packet);
            }
            else if(type == PlayerJoinedMessage)
            {
                processPlayerJoinedMessage(packet);
            }
            else if(type == PlayerRoleSwitchedMessage)
            {
                processPlayerRoleSwitchedMessage(packet);
            }
            else if(type == GameStartMessage)
            {
                processGameStartMessage(packet);
            }
        }
    }
    // remove down stream - do nothing.
    void GameSetup::removeDownStream(PacketDownStream& downStream)
    {
    }

    /**
     * Add a listener 
     */
    void GameSetup::addGameSetupListener(GameSetupListener& listener)
    {
        _gameSetupListeners.push_back(&listener);
    }

    /**
     * Remove a listener.
     */
    void GameSetup::removeGameSetupListener(GameSetupListener& listener)
    {
        for(std::vector<GameSetupListener*>::iterator it = _gameSetupListeners.begin() ; it != _gameSetupListeners.end() ; ++it)
        {
            if(*it == &listener)
            {
                _gameSetupListeners.erase(it);
                break;
            } 
        }
    }

    /**
     * process message - message from client to join game.
     * [AttemptJoinGameMessage]
     */
    void GameSetup::processAttemptToJoinGameMessage(sf::Packet& packet, Connection& connection)
    {
        std::string name;
        if(packet >> name)
        {
            Player player;
            player.uniqueId = connection.name;
            player.name = name;
            player.role = "";
            // make sure that this idiot isnot already joined
            Player* playerPtr = getPlayer(player.uniqueId);
            if(playerPtr != 0)
            {
                // do nothing
            }
            else
            {
                gamesetup_addPlayer(player);
                sendJoinGameSuccessMessage(connection, player);
                sendPlayerJoinMessage(player);
                listener_playerJoined(player);
            }
        }
    }
    
    /**
     * send join game message to server 
     * [AttemptJoinGameMessage]
     */
    void GameSetup::sendJoinMessage()
    {
        sf::Packet packet;
        appendHeader(packet);
        packet << AttemptJoinGameMessage << localName;
        upstream.sendPacketToServer(packet);
    }

    /**
     * Process a leave game message from client
     * [LeaveGameMessage]
     */
    void GameSetup::processLeaveGameMessage(sf::Packet& packet, Connection& connection)
    {
        Player player;
        bool found = false;
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; ++it)
        {    
            if((*it).uniqueId == connection.name)
            {
                player = *it;
                found = true;
                break;
            }
        }
        if(found)
        {
            gamesetup_removePlayer(player.uniqueId);
            sendPlayerLeftMessage(player);
        }
    }
    /**
     * Send a leave game message
     * [LeaveGameMessage]
     */
    void GameSetup::sendLeaveGameMessage()
    {
        sf::Packet packet;
        appendHeader(packet);
        packet << LeaveGameMessage ;
        upstream.sendPacketToServer(packet);
    }

    /**
     * Process a switch role message from client
     * [SwitchRoleMessage]
     */
    void GameSetup::processSwitchRoleMessage(sf::Packet& packet, Connection& connection)
    {
        std::string role;
        if(packet >> role)
        {
            Player* player = getPlayer(connection.name);
            if(player != 0)
            {
                std::string oldRole = player->role;
                gamesetup_setRole(player->uniqueId, role);
                sendPlayerRoleSwitchMessage(*player);
                listener_roleSet(*player, oldRole);
            }
        }
    }

    /**
     * Send to the server to change role
     * [SwitchRoleMessage]
     */
    void GameSetup::sendSwitchRoleMessage(std::string newRole)
    {
        sf::Packet packet;
        appendHeader(packet);
        packet << SwitchRoleMessage << newRole;
        upstream.sendPacketToServer(packet);
    }

    /**
     * Process a join game success message from server. 
     * [JoinGameSuccessMessage]
     */
    void GameSetup::processJoinGameSuccessMessage(sf::Packet& packet)
    {
        std::string name;
        std::string role;
        if(packet >> name >> role)
        {
            listener_joinSuccess(name, role);
            sf::Int32 size;
            packet >> size;
            for(sf::Int32 i = 0 ; i < size ; i++)
            {
                Player tmpPlayer;
                packet >> tmpPlayer.uniqueId >> tmpPlayer.name >> tmpPlayer.role;
                gamesetup_addPlayer(tmpPlayer);
                listener_playerJoined(tmpPlayer);
            }
        }
    }
     
    /**
     * Send a join game success message to a client
     * [JoinGameSuccessMessage]
     */ 
    void GameSetup::sendJoinGameSuccessMessage(Connection& connection, Player player)
    {
        sf::Packet packet;
        appendHeader(packet);
        packet << JoinGameSuccessMessage ;
        packet << player.name << player.role;
        sf::Int32 size = _connectedPlayers.size();
        packet << size;
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; ++it)
        {
            packet << (*it).uniqueId << (*it).name << (*it).role; 
        }
        upstream.sendPacket(connection.name, packet);
    }

    /**
     * Process a player joined game message
     * [PlayerJoinedMessage]
     */
    void GameSetup::processPlayerJoinedMessage(sf::Packet& packet)
    {
        Player player;
        packet >> player.uniqueId >> player.name >> player.role;
        gamesetup_addPlayer(player);
        listener_playerJoined(player);
    }
   
    /**
     * Send PlayerJoinMessage to all players.
     * [PlayerJoinedMessage]
     */ 
    void GameSetup::sendPlayerJoinMessage(Player player)
    {
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; ++it)
        {
            sf::Packet packet;
            appendHeader(packet);
            packet << PlayerJoinedMessage;
            packet << player.uniqueId << player.name << player.role;
            upstream.sendPacket((*it).uniqueId, packet);
        }
    }

    /**
     * Proces a message for role switch.
     * [PlayerRoleSwitchedMessage]
     */
    void GameSetup::processPlayerRoleSwitchedMessage(sf::Packet& packet)
    {
        Player player;
        packet >> player.uniqueId >> player.name >> player.role;
        Player* localPlayer = getPlayer(player.uniqueId);
        if(localPlayer != 0)
        {
            std::string oldRole = localPlayer->role;
            gamesetup_setRole(player.uniqueId, player.role);
            listener_roleSet(player, oldRole);
        }
    }

    /**
     * Send a roleswitch message to all players
     * [PlayerRoleSwitchedMessage]
     */
    void GameSetup::sendPlayerRoleSwitchMessage(Player player)
    {
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; ++it)
        {
            sf::Packet packet;
            appendHeader(packet);
            packet << PlayerRoleSwitchedMessage;
            packet << player.uniqueId << player.name << player.role;
            upstream.sendPacket((*it).uniqueId, packet);
        }
    }

    /**
     * Process a message for a player left that is sent by the server
     */
    void GameSetup::processPlayerLeftMessage(sf::Packet& packet)
    {
        Player player;
        packet >> player.uniqueId >> player.name >> player.role;
        gamesetup_removePlayer(player.uniqueId);
        listener_playerLeft(player);
    }

    /**
     * Send a player left messages to all players
     */
    void GameSetup::sendPlayerLeftMessage(Player player)
    {
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; ++it)
        {
            sf::Packet packet;
            appendHeader(packet);
            packet << PlayerLeftMessage;
            packet << player.uniqueId << player.name << player.role;
            upstream.sendPacket((*it).uniqueId, packet);
        }
    }

    void GameSetup::processGameStartMessage(sf::Packet& packet)
    {
        listener_startGame();
    }

    void GameSetup::sendGameStartMessage()
    {
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; ++it)
        {
            sf::Packet packet;
            appendHeader(packet);
            packet << GameStartMessage;
            upstream.sendPacket((*it).uniqueId, packet); 
        }
    }


///////////////////////////////////////////////// LISTENS FOR DISCONNECT ////////////////    
    void GameSetup::clientConnected(Connection* connection)
    {
    }
    void GameSetup::clientDisconnected(Connection* connection)
    {
    }
    void GameSetup::serverStarted()
    {
    }
    void GameSetup::serverStopped()
    {
    }
    void GameSetup::serverConnected()
    {
    }
    void GameSetup::serverDisconnected()
    {
    }
    void GameSetup::nameInUsed()
    {
    }
    void GameSetup::nameVerified(std::string name)
    {
    }
    void GameSetup::clientVerified(Connection* connection)
    {
    }

/////////// finder methods ///////
    GameSetup::Player* GameSetup::getPlayer(std::string uniqueId)
    {
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; ++it)
        {
            if((*it).uniqueId == uniqueId)
            {
                return &(*it);
            } 
        }
        return 0;
    }
    /////////////////// /////
    void GameSetup::gamesetup_addPlayer(Player p)
    {
        _connectedPlayers.push_back(p);
    }
    
    void GameSetup::gamesetup_removePlayer(std::string uniqueId)
    {
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; )
        {    
            if((*it).uniqueId == uniqueId)
            {
                it = _connectedPlayers.erase(it);
                break;
            }
            ++it;
        }
    }
    
    void GameSetup::gamesetup_setRole(std::string uniqueId, std::string role)
    {
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; ++it)
        {
            if((*it).uniqueId == uniqueId)
            {
                (*it).role = role;
                break;
            } 
        }
    }
    ///////////////////
    void GameSetup::listener_joinSuccess(std::string name, std::string role)
    {
        for(std::vector<GameSetupListener*>::iterator it = _gameSetupListeners.begin() ; it != _gameSetupListeners.end() ; ++it)
        {
            (*it)->joinSuccess(name, role);
        }
    }

    void GameSetup::listener_playerJoined(Player player)
    {
        for(std::vector<GameSetupListener*>::iterator it = _gameSetupListeners.begin() ; it != _gameSetupListeners.end() ; ++it)
        {
            (*it)->playerJoined(player.uniqueId, player.name, player.role); 
        }
    }

    void GameSetup::listener_roleSet(Player player, std::string oldRole)
    {
        for(std::vector<GameSetupListener*>::iterator it = _gameSetupListeners.begin() ; it != _gameSetupListeners.end() ; ++it)
        {
            (*it)->playerSwitchRole(player.uniqueId, player.name, oldRole, player.role); 
        }
    }

    void GameSetup::listener_playerLeft(Player player)
    {
        for(std::vector<GameSetupListener*>::iterator it = _gameSetupListeners.begin() ; it != _gameSetupListeners.end() ; ++it)
        {
            (*it)->playerLeft(player.uniqueId, player.name, player.role); 
        }
    }
    
    void GameSetup::listener_startGame()
    {
        for(std::vector<GameSetupListener*>::iterator it = _gameSetupListeners.begin() ; it != _gameSetupListeners.end() ; ++it)
        {
            (*it)->gameStarts(); 
        }
    }
    ////// Public API ////// 
    bool GameSetup::ready()
    {
        if(_isHosting)
        {
            //if i am the host, naturally I will be the only one when this function call.
            Player p;
            p.name = localName;
            p.uniqueId = upstream.getUniqueId();
            p.role = "";
            gamesetup_addPlayer(p);
            listener_playerJoined(p);
        }
    }
    
    void GameSetup::joinServer()
    {
        if(!_isHosting)
        {
            sendJoinMessage();
        }
    }

    void GameSetup::setRole(std::string role)
    {
        if(_isHosting)
        {
            //find myself
            Player* player = getPlayer(localName);
            if(player != 0)
            {
                std::string oldRole = player->role;
                // shouldn't have to check but just in case
                gamesetup_setRole(player->uniqueId, role);
                sendPlayerRoleSwitchMessage(*player);
                listener_roleSet(*player, oldRole);
            }
        }
        else
        {
            sendSwitchRoleMessage(role);
        }
    }

    void GameSetup::assignRole(std::string uniqueId, std::string role)
    {
        if(_isHosting)
        {
            Player* player = getPlayer(uniqueId);
            if(player != 0)
            {
                std::string oldRole = player->role;
                gamesetup_setRole(player->uniqueId, role);
                sendPlayerRoleSwitchMessage(*player);
                listener_roleSet(*player, oldRole);
            }
        }
    }

    void GameSetup::startGame()
    {
        listener_startGame();
        sendGameStartMessage();
    }

    std::vector<std::string> GameSetup::getUniqueId(std::string role)
    {
        std::vector<std::string> str;
        for(std::vector<Player>::iterator it = _connectedPlayers.begin() ; it != _connectedPlayers.end() ; ++it)
        {
            if((*it).role == role)
            {
                str.push_back((*it).uniqueId);
            }        
        }
        return str;
    }

    std::string GameSetup::getLocalRole()
    {
        // should never be 0.
        Player* player = getPlayer(localName);
        return player->role;
    }

    const std::vector<GameSetup::Player>& GameSetup::getPlayers()
    {
        return _connectedPlayers;
    }
}


