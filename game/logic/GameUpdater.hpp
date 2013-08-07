#ifndef _GAME_LOGIC_GAMEUPDATER_H_
#define _GAME_LOGIC_GAMEUPDATER_H_
#include "../constants.hpp"
#include "../messages/g_messages.hpp"
/**
 * GameUpdater defines the abstract class for a source of updater.
 * This define the source of messages that the battle object that can read from to update the game.
 *
 */
class GameUpdater
{
public:
    GameUpdater(PlayerRole::ePlayerRole r);
    virtual bool isConnected() = 0;
    /**
     * returns the next message for the battle object.
     * The battle object will free the message upon consumption. 
     */
    virtual Message* popNextMessage() = 0;

    PlayerRole::ePlayerRole role;
};
#endif
