#include "Battle.hpp"
#include "GameViewer.hpp"
#include "GameUpdater.hpp"
#include "BattleServer.hpp"
#include "../../z_framework/zf_common/debugging.hpp"
#include <iostream>
Battle::Battle(BattleServer& battleServer)
    :_server(&battleServer), isServer(false), currentPlayer(_currentPlayer), _battleState(PreGame)
{
}

Battle::Battle()
    :_server(0), isServer(true), currentPlayer(_currentPlayer), _battleState(PreGame)
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

void Battle::removeGameViewer(GameViewer* viewer)
{
    for(std::vector<GameViewer*>::iterator it = _viewers.begin() ; it != _viewers.end() ; )
    {    
        if(*it == viewer)
        {
            it = _viewers.erase(it);
            continue;
        }
        ++it;
    }
}

void Battle::removeGameUpdater(GameUpdater* updater)
{
    for(std::vector<GameUpdater*>::iterator it = _updaters.begin() ; it != _updaters.end() ; )
    {    
        if(*it == updater)
        {
            it = _updaters.erase(it);
            continue;
        }
        ++it;
    }
}

std::vector<Die> Battle::getDice()
{
    return _currentDice;
}

// This is for message from server (cannot be wrong)
void Battle::processServerMessage(Message* message)
{
    if(message->type == Message::GameStartMessage)
    {
        DB_GameStartMessage* m = (DB_GameStartMessage*)message;
        gamelogic_startGame(m->rules, m->player1, m->player2);
    }
    else if(message->type == Message::ActiveTurnMessage)
    {
        DB_ActiveTurnMessage* m = (DB_ActiveTurnMessage*)message;
        gamelogic_setActiveTurn(m->currentPlayer, m->burnDamage, m->availableDice, m->frozenDice, m->rollableDice);
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
    else if(message->type == Message::NewDiceMessage)
    {
        DB_NewDiceMessage* m = (DB_NewDiceMessage*)message;
        gamelogic_newDice(m->dice);
    }
    else if(message->type == Message::EndTurnMessage)
    {
        DB_EndTurnMessage* m = (DB_EndTurnMessage*)message;
        gamelogic_endTurn(m->damageTaken);
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
    if(actor == currentPlayer)
    {
    }
    else
    {
    }
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

void Battle::sendClientMessage(PlayerRole::ePlayerRole actor, Message* message)
{
    if(message->type == Message::SendDoneCommand)
    {
        DB_SendDoneCommand* m = (DB_SendDoneCommand*)message;
        if(currentPlayer == actor || actor == PlayerRole::Both)
        {
            sf::Packet packet;
            _server->appendHeader(packet);
            packet << m->type << *m;
            if(_server != 0)
            {
                _server->sendPacketToServer(packet);
            }
        }
    }
    else if(message->type == Message::SendRollCommand)
    {
        DB_SendRollCommand* m = (DB_SendRollCommand*)message;
        if(currentPlayer == actor || actor == PlayerRole::Both)
        {
            sf::Packet packet;
            _server->appendHeader(packet);
            packet << m->type << *m;
            if(_server != 0)
            {
                _server->sendPacketToServer(packet);
            }
        }
    }
    else if(message->type == Message::SendUseAbilityCommand)
    {
        DB_SendUseAbilityCommand* m = (DB_SendUseAbilityCommand*)message;
        if(currentPlayer == actor || actor == PlayerRole::Both)
        {
            sf::Packet packet;
            _server->appendHeader(packet);
            packet << m->type << *m;
            if(_server != 0)
            {
                _server->sendPacketToServer(packet);
            }
        }
    }
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
            if(isServer)
            {
                processClientMessage((*it)->role, message);
                message = (*it)->popNextMessage();
            }
            else
            {
                sendClientMessage((*it)->role, message);
                message = (*it)->popNextMessage();
            }
        }
    }
}

void Battle::startGame(Rules& rules, std::string player1Name, std::string player2Name)
{
    // make sure the state is correct
    if(_battleState != PreGame)
    {
        return;
    }
    // set the rule value
    sf::Int32 startingHp = rules.getStartingHp();
    std::vector<Die> dice = rules.getDice();
    std::vector<Ability> abilities = rules.getAbilities();
    Unit u1(player1Name, startingHp, dice.size());
    Unit u2(player2Name, startingHp, dice.size());
    gamelogic_startGame(rules,u1,u2);
    
    // randomly get the active player.
    PlayerRole::ePlayerRole activePlayer = PlayerRole::randomPlayer();
    Unit& unit = _units[activePlayer]; 
    gamelogic_setActiveTurn(activePlayer, unit.burnCounter, unit.diceCounter, unit.freezeCounter, dice);
}

Die Battle::findDie(sf::Int32 id)
{
    for(std::vector<Die>::iterator it = _currentDice.begin() ; it != _currentDice.end() ; ++it)
    {
        if((*it).id == id)
        {
            return *it;
        } 
    }
    return Die();
}

std::vector<Die> Battle::findDice(std::vector<sf::Int32> ids)
{
    std::vector<Die> dice;
    for(std::vector<sf::Int32>::iterator it = ids.begin() ; it != ids.end() ; ++it)
    {
        Die d = findDie(*it);
        // make sure that the id is the same.
        if(d.id == *it)
        {
            dice.push_back(d);
        }
    }
    return dice;
}
