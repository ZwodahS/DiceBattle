#ifndef _GAME_LOGIC_GAMESCREENVIEWER_H_
#define _GAME_LOGIC_GAMESCREENVIEWER_H_
#include "../logic/GameViewer.hpp"
class GameScreen;
class GameScreenViewer : public GameViewer
{
public:
    GameScreenViewer(PlayerRole::ePlayerRole r, GameScreen& gameScreen);

    bool isConnected();

    void sendMessage(DB_GameStartMessage message);
    void sendMessage(DB_ActiveTurnMessage message);
    void sendMessage(DB_AskForActionMessage message);
    void sendMessage(DB_AbilityUsedMessage message);
    void sendMessage(DB_DiceRolledResultMessage message);
    void sendMessage(DB_EndTurnMessage message);
    void sendMessage(DB_EndGameMessage message);
    void sendMessage(DB_NewDiceMessage message);
private:
    GameScreen* gameScreen;
};
#endif
