#include "GameScreenViewer.hpp"
#include "GameScreen.hpp"

GameScreenViewer::GameScreenViewer(PlayerRole::ePlayerRole r)
    :GameViewer(r), gameScreen(0)
{
}

void GameScreenViewer::setGameScreen(GameScreen* gameScreen)
{
    this->gameScreen = gameScreen;
}

bool GameScreenViewer::isConnected()
{
    return this->gameScreen != 0 ;
}

void GameScreenViewer::sendMessage(DB_GameStartMessage message)
{
    if(gameScreen!=0)
    {
        gameScreen->sendMessage(message);
    }
}
void GameScreenViewer::sendMessage(DB_ActiveTurnMessage message)
{
    if(gameScreen!=0)
    {
        gameScreen->sendMessage(message);
    }
}
void GameScreenViewer::sendMessage(DB_AskForActionMessage message)
{
    if(gameScreen!=0)
    {
        gameScreen->sendMessage(message);
    }
}
void GameScreenViewer::sendMessage(DB_AbilityUsedMessage message)
{
    if(gameScreen!=0)
    {
        gameScreen->sendMessage(message);
    }
}
void GameScreenViewer::sendMessage(DB_DiceRolledResultMessage message)
{
    if(gameScreen!=0)
    {
        gameScreen->sendMessage(message);
    }
}
void GameScreenViewer::sendMessage(DB_EndTurnMessage message)
{
    if(gameScreen!=0)
    {
        gameScreen->sendMessage(message);
    }
}
void GameScreenViewer::sendMessage(DB_EndGameMessage message)
{
    if(gameScreen!=0)
    {
        gameScreen->sendMessage(message);
    }
}
