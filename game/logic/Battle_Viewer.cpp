#include "Battle.hpp"
#include "GameViewer.hpp"
#include "GameUpdater.hpp"
#include "../messages/g_messages.hpp"
#include "../../z_framework/zf_common/debugging.hpp"
void Battle::viewer_sendStartGameMessages(const Rules& rules, const Unit& player1, const Unit& player2)
{
    for(std::vector<GameViewer*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it)
    {
        if((**it).isConnected())
        {
            DB_GameStartMessage message(rules,player1, player2);
            (**it).sendMessage(message);
        }
    }
}
void Battle::viewer_sendActiveTurnMessages(const PlayerRole::ePlayerRole& currentPlayer, sf::Int32 burn, sf::Int32 available, sf::Int32 frozen, std::vector<Die> dice)
{
    for(std::vector<GameViewer*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it)
    {
        if((**it).isConnected())
        {
            DB_ActiveTurnMessage message(currentPlayer, burn, available, frozen,dice);
            (**it).sendMessage(message);
        }
    }
}

void Battle::viewer_sendDiceRolledMessages(std::vector<Die> dice)
{
    for(std::vector<GameViewer*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it)
    {
        if((**it).isConnected())
        {
            DB_DiceRolledResultMessage message(dice);
            (**it).sendMessage(message);
        } 
    }
}
void Battle::viewer_sendAbilityUsedMessages(const PlayerRole::ePlayerRole& user, const Ability& abilityUsed, std::vector<sf::Int32> diceUsed)
{
    for(std::vector<GameViewer*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it)
    {
        if((**it).isConnected())
        {
            DB_AbilityUsedMessage message(user, abilityUsed, diceUsed);
            (**it).sendMessage(message);
        }
    }
}

void Battle::viewer_sendNewDiceMessages(std::vector<Die>& dice)
{
    for(std::vector<GameViewer*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it)
    {
        if((**it).isConnected())
        {
            DB_NewDiceMessage message(dice);
            (**it).sendMessage(message);
        } 
    }
}

void Battle::viewer_sendEndTurnMessages(sf::Int32 damage)
{
    for(std::vector<GameViewer*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it)
    {
        if((**it).isConnected())
        {
            DB_EndTurnMessage message(damage);
            (**it).sendMessage(message);
        }
    }
}
void Battle::viewer_sendEndGameMessages(PlayerRole::ePlayerRole winner)
{
    for(std::vector<GameViewer*>::iterator it = _viewers.begin() ; it != _viewers.end() ; ++it) {
        if((**it).isConnected())
        {
            DB_EndGameMessage message(winner);
            (**it).sendMessage(message);
        }
    }
}
