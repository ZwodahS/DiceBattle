#ifndef _GAME_LOGIC_GAMEUPDATER_H_
#define _GAME_LOGIC_GAMEUPDATER_H_
/**
 * GameUpdater defines the abstract class for a source of updater.
 * This define the source of messages that the battle object that can read from to update the game.
 *
 */
class GameUpdater
{
public:
    virtual bool isConnected() = 0;
    /**
     * returns the next message for the battle object.
     * The battle object will free the message upon consumption. 
     */
    virtual Message* popNextMessage() = 0;

    PlayerRole::ePlayerRole role;
};
#endif
