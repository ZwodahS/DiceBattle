#ifndef _GAME_LOGIC_GAMEVIWER_H_
#define _GAME_LOGIC_GAMEVIWER_H_
/** 
 * GameViewer defines the abstract super class for a viewer of a battle.
 * This allow me to hide what type of player this is from the battle object,
 * so it do not need to know if the player is a A.I. or a local player or a 
 * player across the net.
 */
class GameViewer
{
    virtual bool isConnected() = 0;
};
#endif
