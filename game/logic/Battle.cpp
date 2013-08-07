#include "Battle.hpp"
#include "GameViewer.hpp"
#include "GameUpdater.hpp"
#include "BattleServer.hpp"
Battle::Battle(BattleServer& battleServer)
    :_server(&battleServer), isServer(false), currentPlayer(_currentPlayer)
{

}

Battle::Battle()
    :_server(0), isServer(true), currentPlayer(_currentPlayer)
{
}

Battle::~Battle()
{
}

Unit& Battle::getUnit(PlayerRole::ePlayerRole p)
{
    if(p != PlayerRole::PlayerOne && p != PlayerRole::PlayerTwo)
    {
        return _units[PlayerRole::PlayerOne];
    }
    return _units[p];
}

void Battle::addGameViewer(GameViewer* viewer)
{
    this->_viewers.push_back(viewer);
}

void Battle::addGameUpdater(GameUpdater* updater)
{
    this->_updaters.push_back(updater);
}

// This is for message from server (cannot be wrong)
void Battle::processServerMessage(Message* message)
{
    if(message->type == Message::GameStartMessage)
    {
        DB_GameStartMessage* m = (DB_GameStartMessage*)message;
        gamelogic_startGame(m->player1, m->player2);
    }
    else if(message->type == Message::ActiveTurnMessage)
    {
        DB_ActiveTurnMessage* m = (DB_ActiveTurnMessage*)message;
        gamelogic_setActiveTurn(m->currentPlayer, m->burnDamage, m->availableDice, m->frozenDice);
    }
    else if(message->type == Message::AskForActionMessage)
    {
    }
    else if(message->type == Message::DiceRolledResultMessage)
    {
        DB_DiceRolledResultMessage* m = (DB_DiceRolledResultMessage*)message;
        gamelogic_setDiceRolled(m->rolledDice);
    }
    else if(message->type == Message::AbilityUsedMessage)
    {
        DB_AbilityUsedMessage* m = (DB_AbilityUsedMessage*)message;
        gamelogic_abilityUsed(m->user, m->abilityUsed, m->diceUsed);
    }
    else if(message->type == Message::EndTurnMessage)
    {
        DB_EndTurnMessage* m = (DB_EndTurnMessage*)message;
        gamelogic_endTurn();
    }
    else if(message->type == Message::EndGameMessage)
    {
        DB_EndGameMessage* m = (DB_EndGameMessage*)message;
        gamelogic_endGame(m->winner);
    }
    delete message;
}

void Battle::processClientMessage(PlayerRole::ePlayerRole actor, Message* message)
{
    if(message->type == Message::SendDoneCommand)
    {
        DB_SendDoneCommand* m = (DB_SendDoneCommand*)message;
        if(currentPlayer == actor || actor == PlayerRole::Both)
        {
            gamelogic_receivedDoneCommand();
        }
    }
    else if(message->type == Message::SendRollCommand)
    {
        DB_SendRollCommand* m = (DB_SendRollCommand*)message;
        if(currentPlayer == actor || actor == PlayerRole::Both)
        {
            gamelogic_receivedRollCommand(m->diceId);
        }
    }
    else if(message->type == Message::SendUseAbilityCommand)
    {
        DB_SendUseAbilityCommand* m = (DB_SendUseAbilityCommand*)message;
        if(currentPlayer == actor || actor == PlayerRole::Both)
        {
            gamelogic_receivedUseAbilityCommand(m->abilityUsed, m->diceUsed);
        }
    }
    delete message;
}

void Battle::update()
{
    // process the message from the server.
    if(_server != 0 && !isServer)
    {
        Message* message = (*_server).popNextMessage();
        while(message != 0)
        {
            processServerMessage(message);
            message = 0;
            message = (*_server).popNextMessage();
        }
    }
    for(std::vector<GameUpdater*>::iterator it = _updaters.begin() ; it != _updaters.end() ; ++it)
    {
        Message* message = (*it)->popNextMessage();     
        while(message != 0)
        {
            processClientMessage((*it)->role, message);
            message = (*it)->popNextMessage();
        }
    }
}


