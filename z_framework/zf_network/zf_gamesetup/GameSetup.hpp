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
#ifndef _ZF_ZFNETWORK_GAMESETUP_H_
#define _ZF_ZFNETWORK_GAMESETUP_H_
#include "../PacketUpStream.hpp"
#include "../PacketDownStream.hpp"
#include "../ConnectionListener.hpp"
#include "GameSetupListener.hpp"
#include <string>
#include <vector>
namespace zf
{
    /**
     * How to use Game Setup :
     *
     * GameSetup uses the ConnectionManager to manage the connections. It only deals with joining/hosting a game.
     *
     * GameSetup is both a upstream and a downstream.
     * The existence of the Upstream is just in case that this can be extended further in the future.
     * The Downstream provide an interface for ConnectionManager to forward the message to.
     *
     * Both the client and the server needs to have an object on their side.
     * This object will take care of keeping them in sync and will inform the listeners that things has changed.
     *
     * A typical flow for GameSetup will be :
     *
     * 1. A Player decided to host a game. 
     *       In the code, create a GameSetup object to host the game.
     *       The GameSetup constructor take 3 value.
     *          localName : the display name used by this player.
     *          upstream : Usually a ConnectionManager but can be any upstream to send the message to.
     *          header : the message header to identify your message from the siblings node.
     *       Add listeners to this game setup object. (i.e. the lobby screen)
     *       Add this object to the upstream.
     *       You are ready to listen for player joining.
     * 2. A Player connects to the host. (In ConnectionManager).
     * 3. Player request to join game.
     *       In the Code, create a GameSetup object on joiner side. 
     *       Add the listeners to Gamesetup.
     *       Add this object to upstream.
     *       send a join game message to server, using the public method of GameSetup.
     */
    class GameSetup : public PacketUpStream, public PacketDownStream, public ConnectionListener
    {
    public:
        
        /**
         * Local Name representing what the name is.
         */
        GameSetup(std::string localName, PacketUpStream& upstream, sf::Int32 header, bool hosting);
        ~GameSetup();
        virtual void appendHeader(sf::Packet& packet);
        virtual sf::Int32 getHeader();
        virtual void packetReceived(sf::Packet& packet, Connection& connection);
        virtual void packetReceivedFromServer(sf::Packet& packet);
        virtual Connection* getConnection(std::string name);
        virtual bool sendPacket(std::string& name, sf::Packet& packet);
        virtual bool sendPacketToServer(sf::Packet& packet);
        virtual std::string getUniqueId();
        virtual void removeDownStream(PacketDownStream& downStream);
        std::string localName;
        bool isHosting();
    



        PacketUpStream& upstream;
        /// manage listener for game setup
        void addGameSetupListener(GameSetupListener& listener);
        void removeGameSetupListener(GameSetupListener& listener);
        /// connection listener methods/
        /**
         * Only a few methods are implemented.
         */
        void clientConnected(Connection* connection);
        void clientDisconnected(Connection* connection);
        void serverStarted();
        void serverStopped();
        void serverConnected();
        void serverDisconnected();
        void nameInUsed();
        void nameVerified(std::string name);
        void clientVerified(Connection* connection);
        struct Player
        {
            // unique id is to get the connection object
            std::string uniqueId;
            // name is the identifier in the game.
            std::string name;
            // the role
            std::string role;
        };
        /**
         * Call this once all the listeners and stuffs are set up.
         * Call this only once. This must be called before ANY message is received, or you are screwed.
         * Call this only if you are hosting.
         */
        bool ready();
        /**
         * This will send a join message to server. It will send a join success message if the join is success.
         */
        void joinServer();

        ////////////////////// PUBLIC API ///////////////////
        /**
         * Set the role. If you are the server, it will just update locally and send it to all client
         * If you are the client, it will send the message to server
         */
        void setRole(std::string role);
        /**
         * This can only be called by the host at the moment.
         */
        void assignRole(std::string uniqueId, std::string role);
        /**
         * Inform all client that the game has started.
         */
        void startGame();
        /**
         * Get the uniqueId of the players that are of a certain role
         */
        std::vector<std::string> getUniqueId(std::string role);
        /**
         * Get local role
         */
        std::string getLocalRole();
        const std::vector<Player>& getPlayers();
    private:
        std::vector<GameSetupListener*> _gameSetupListeners;
        bool _isHosting;
        sf::Int32 _header;

        const static sf::Int32 AttemptJoinGameMessage = 1000;
        const static sf::Int32 LeaveGameMessage = 1001;
        const static sf::Int32 SwitchRoleMessage = 1002;

        const static sf::Int32 JoinGameSuccessMessage = 2001;
        const static sf::Int32 PlayerJoinedMessage = 2002;
        const static sf::Int32 PlayerLeftMessage = 2003;
        const static sf::Int32 PlayerRoleSwitchedMessage = 2004;
        const static sf::Int32 GameStartMessage = 2005;

        void processAttemptToJoinGameMessage(sf::Packet& packet, Connection& connection);
        void sendJoinMessage();
        void processLeaveGameMessage(sf::Packet& packet, Connection& connection);
        void sendLeaveGameMessage();
        void processSwitchRoleMessage(sf::Packet& packet, Connection& connection);
        void sendSwitchRoleMessage(std::string newRole);

        void processJoinGameSuccessMessage(sf::Packet& packet);
        void sendJoinGameSuccessMessage(Connection& connection, Player player);
        void processPlayerJoinedMessage(sf::Packet& packet);
        void sendPlayerJoinMessage(Player player);
        void processPlayerRoleSwitchedMessage(sf::Packet& packet);
        void sendPlayerRoleSwitchMessage(Player player);
        void processPlayerLeftMessage(sf::Packet& packet);
        void sendPlayerLeftMessage(Player player);
        void processGameStartMessage(sf::Packet& packet);
        void sendGameStartMessage();
        std::vector<Player> _connectedPlayers;

        
        /// functions for sending messages to all listeners.
        void listener_joinSuccess(std::string name, std::string role);
        void listener_playerJoined(Player player);
        void listener_playerLeft(Player player);
        void listener_roleSet(Player player, std::string oldRole);
        void listener_startGame();
        /// functions for actual processing.
        void gamesetup_addPlayer(Player player);
        void gamesetup_removePlayer(std::string uniqueId);
        void gamesetup_setRole(std::string uniqueId, std::string role);

        Player* getPlayer(std::string uniqueId);
    };
}

#endif
