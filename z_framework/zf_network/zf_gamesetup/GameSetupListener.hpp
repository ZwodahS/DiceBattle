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
#ifndef _ZF_NETWORK_GAMESETUPLISTENER_H_
#define _ZF_NETWORK_GAMESETUPLISTENER_H_
#include <string>
namespace zf
{
    /**
     * GameSetupListener interface for processing game setup message.
     */
    class GameSetupListener
    {
    public:
        /**
         * Process game start.
         */
        virtual void gameStarts() = 0;
        /**
         * Inform the listener that "we" have successfully join a game
         *  name - The name we are given or using.
         *  role - the string representing the role.
         */
        virtual void joinSuccess(std::string name, std::string role) = 0;
        /**
         * Inform the listener that a player has join a game that we are in.
         *  uniqueId - the uniqueId given to the player.
         *  name - the display name of the player.
         *  role - the role of the player.
         */
        virtual void playerJoined(std::string uniqueId, std::string name, std::string role) = 0;
        /**
         * Inform the listener that a player's role has been changed.
         *  uniqueId - the uniqueId given to the player.
         *  name - the display name of the player.
         *  role - the role of the player.
         */
        virtual void playerSwitchRole(std::string uniqueId, std::string name, std::string oldRole, std::string newRole) = 0;
        /**
         * Inform the listener that a player has left the game.
         *  uniqueId - the uniqueId given to the player.
         *  name - the display name of the player.
         *  role - the role of the player.
         */
        virtual void playerLeft(std::string uniqueId, std::string name, std::string role) = 0;
    };
}
#endif
