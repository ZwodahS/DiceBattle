#ifndef _GAME_LOGIC_GAMEVIEWER_H_
#define _GAME_LOGIC_GAMEVIEWER_H_
#include "../messages/g_messages.hpp"
/** 
 * GameViewer defines the abstract super class for a viewer of a battle.
 * This allow me to hide what type of player this is from the battle object,
 * so it do not need to know if the player is a A.I. or a local player or a 
 * player across the net.
 */
class GameViewer
{
public:
    GameViewer(PlayerRole::ePlayerRole r = PlayerRole::Observer);

    virtual bool isConnected() = 0;

    virtual void sendMessage(DB_GameStartMessage message) = 0;
    virtual void sendMessage(DB_ActiveTurnMessage message) = 0;
    virtual void sendMessage(DB_AskForActionMessage message) = 0;
    virtual void sendMessage(DB_AbilityUsedMessage message) = 0;
    virtual void sendMessage(DB_DiceRolledResultMessage message) = 0;
    virtual void sendMessage(DB_NewDiceMessage message) = 0;
    virtual void sendMessage(DB_EndTurnMessage message) = 0;
    virtual void sendMessage(DB_EndGameMessage message) = 0;

    PlayerRole::ePlayerRole role;
};
#endif
