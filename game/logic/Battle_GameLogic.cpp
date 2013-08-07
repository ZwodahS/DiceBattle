#include "Battle.hpp"
#include "GameViewer.hpp"
#include "GameUpdater.hpp"

void Battle::gamelogic_startGame(const Unit& player1, const Unit& player2)
{
    _units[PlayerRole::PlayerOne] = player1;
    _units[PlayerRole::PlayerTwo] = player2;
    viewer_sendStartGameMessages(player1, player2);
}

void Battle::gamelogic_setActiveTurn(const PlayerRole::ePlayerRole& cp, sf::Int32 burn, sf::Int32 available, sf::Int32 frozen)
{
    _currentPlayer = cp;
    _units[_currentPlayer].currentHp -= burn;
    _units[_currentPlayer].burnCounter = _units[_currentPlayer].burnCounter > 0 ? _units[_currentPlayer].burnCounter - 1 : 0;
    viewer_sendActiveTurnMessages(cp, burn, available, frozen);
}

void Battle::gamelogic_setDiceRolled(Die& die)
{
    // find the die and set it
    for(std::vector<Die>::iterator it = _currentDice.begin() ; it != _currentDice.end() ; ++it)
    {
        if((*it).id == die.id)
        {
            *it = die;
            break;
        }
    }
}

void Battle::gamelogic_setDiceRolled(std::vector<Die> dice)
{
    for(std::vector<Die>::iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        gamelogic_setDiceRolled(*it);    
    }
    viewer_sendDiceRolledMessages(dice);
}

void Battle::gamelogic_removeDice(std::vector<sf::Int32> dices)
{
    for(std::vector<sf::Int32>::iterator it = dices.begin() ; it != dices.end() ; ++it)
    {
        for(std::vector<Die>::iterator it2 = _currentDice.begin() ; it2 != _currentDice.end() ; )
        {  
            if((*it) == (*it2).id)
            {
                it2 = _currentDice.erase(it2);
                break;
            }
            ++it2;
        }
    }
}

void Battle::gamelogic_abilityUsed(const PlayerRole::ePlayerRole& user, const Ability& abilityUsed, std::vector<sf::Int32> diceUsed)
{
    gamelogic_removeDice(diceUsed);
    Unit& userUnit = getUnit(user);
    Unit& opponentUnit = getUnit(PlayerRole::opponentOf(user));
    for(std::vector<AbilityEffect>::const_iterator it = abilityUsed.effects.begin() ; it != abilityUsed.effects.end() ; ++it)
    {
        switch((*it).type)
        {
            case AbilityType::PhysicalDamage: 
                if(opponentUnit.shieldCounter >= (*it).value)
                {
                    opponentUnit.shieldCounter -= (*it).value;
                }
                else
                {
                    opponentUnit.currentHp -= ((*it).value - opponentUnit.shieldCounter);
                    opponentUnit.shieldCounter = 0;
                }
                break;
            case AbilityType::MagicalDamage:
                opponentUnit.currentHp -= (*it).value;
                break;
            case AbilityType::Shield:
                userUnit.shieldCounter += (*it).value;
                break;
            case AbilityType::Heal:
                userUnit.currentHp += (*it).value;
                userUnit.currentHp = userUnit.currentHp > userUnit.maxHp ? userUnit.maxHp : userUnit.currentHp;
                break;
            case AbilityType::Burn:
                opponentUnit.burnCounter += (*it).value;
                break;
            case AbilityType::Freeze:
                opponentUnit.freezeCounter += (*it).value;
                break;
            case AbilityType::Shock:
                opponentUnit.shockCounter += (*it).value;
                break;
            default:
                break;
        }
    }
    viewer_sendAbilityUsedMessages(user,abilityUsed,diceUsed);
}

void Battle::gamelogic_endTurn()
{
    Unit& currentUnit = getUnit(_currentPlayer);
    currentUnit.shockCounter = 0;
    currentUnit.freezeCounter = 0;
    viewer_sendEndTurnMessages();
}

void Battle::gamelogic_endGame(PlayerRole::ePlayerRole winner)
{
    viewer_sendEndGameMessages(winner);
}


////////// commands from updater ////

void Battle::gamelogic_receivedDoneCommand()
{

}

void Battle::gamelogic_receivedRollCommand(const std::vector<sf::Int32>& diceId)
{

}

void Battle::gamelogic_receivedUseAbilityCommand(const Ability& abilityUsed, const std::vector<sf::Int32>& diceUsed)
{

}
