#include "Battle.hpp"
#include "GameViewer.hpp"
#include "GameUpdater.hpp"
#include "../../z_framework/zf_common/debugging.hpp"
#include <iostream>
void Battle::gamelogic_startGame(Rules& rules, const Unit& player1, const Unit& player2)
{
    viewer_sendStartGameMessages(rules, player1, player2);
    _units[PlayerRole::PlayerOne] = player1;
    _units[PlayerRole::PlayerTwo] = player2;
    this->rules = rules;
}

void Battle::gamelogic_setActiveTurn(const PlayerRole::ePlayerRole& cp, sf::Int32 burn, sf::Int32 available, sf::Int32 frozen, std::vector<Die> dice)
{
    viewer_sendActiveTurnMessages(cp, burn, available, frozen,dice);
    // assign the current player
    _currentPlayer = cp; 
    // deal damage to the player equals to their burn counter
    _units[_currentPlayer].currentHp -= burn;
    // reduce the counter by 1 if it is more than 0
    _units[_currentPlayer].burnCounter = _units[_currentPlayer].burnCounter > 0 ? _units[_currentPlayer].burnCounter - 1 : 0;
    // set the new set of dice
    _currentDice = dice;
    // set the state to pre roll
    _battleState = PreRoll;
}

void Battle::gamelogic_setDiceRolled(Die& die)
{
    bool found = false;
    // find the die and set it
    for(std::vector<Die>::iterator it = _currentDice.begin() ; it != _currentDice.end() ; ++it)
    {
        if((*it).id == die.id)
        {
            *it = die;
            found = true;
            break;
        }
    }
    // if the die is not found, then just add it to the list
    if(!found)
    {
        _currentDice.push_back(die);
    }
}

void Battle::gamelogic_setDiceRolled(std::vector<Die> dice)
{
    viewer_sendDiceRolledMessages(dice);
    // for every die, set the dice value.
    for(std::vector<Die>::iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        gamelogic_setDiceRolled(*it);    
    }
    // set the state to dice rolled
    _battleState = DiceRolled;
}

void Battle::gamelogic_removeDice(std::vector<sf::Int32> dices)
{
    // remove all the dice matching the id
    // remove as much as possible
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
    // send it to all viewer.
    viewer_sendAbilityUsedMessages(user,abilityUsed,diceUsed);
    // remove all the dice matching the used dice
    gamelogic_removeDice(diceUsed);
    // get the current unit.
    Unit& userUnit = getUnit(user);
    // get the opponent of current unit.
    Unit& opponentUnit = getUnit(PlayerRole::opponentOf(user));
    // for every ability effects of this ability
    for(std::vector<AbilityEffect>::const_iterator it = abilityUsed.effects.begin() ; it != abilityUsed.effects.end() ; ++it)
    {
        // depend on the type, process the effect.
        switch((*it).type)
        {
            // physical damage
            case AbilityType::PhysicalDamage: 
                // if the shield is higher than value, then just subtract it from the shield
                if(opponentUnit.shieldCounter >= (*it).value)
                {
                    opponentUnit.shieldCounter -= (*it).value;
                }
                // if the shield is lower than the damage, then remove all shield counter and deal the remaining to hp
                else
                {
                    opponentUnit.currentHp -= ((*it).value - opponentUnit.shieldCounter);
                    opponentUnit.shieldCounter = 0;
                }
                break;
            // magical damage
            case AbilityType::MagicalDamage:
                // magical damage deals directly to hp, bypass shield.
                opponentUnit.currentHp -= (*it).value;
                break;
            // shield
            case AbilityType::Shield:
                // just increase the shield counter for the current unit
                userUnit.shieldCounter += (*it).value;
                break;
            // heal
            case AbilityType::Heal:
                // increase the hp
                userUnit.currentHp += (*it).value;
                // make sure it did not exceed maxhp
                userUnit.currentHp = userUnit.currentHp > userUnit.maxHp ? userUnit.maxHp : userUnit.currentHp;
                break;
            // Burn 
            case AbilityType::Burn:
                // increase the burn counter
                opponentUnit.burnCounter += (*it).value;
                break;
            // Freeze
            case AbilityType::Freeze:
                // increase the freeze counter
                opponentUnit.freezeCounter += (*it).value;
                break;
            // Shock
            case AbilityType::Shock:
                // Increase the shock counter
                opponentUnit.shockCounter += (*it).value;
                break;
            default:
                break;
        }
    }
    _battleState = AbilityUsed;
}

void Battle::gamelogic_endTurn(sf::Int32 damage)
{
    viewer_sendEndTurnMessages(damage);
    Unit& currentUnit = getUnit(_currentPlayer);
    currentUnit.currentHp -= damage;
    currentUnit.shockCounter = 0;
    currentUnit.freezeCounter = 0;
}

void Battle::gamelogic_endGame(PlayerRole::ePlayerRole winner)
{
    viewer_sendEndGameMessages(winner);
}

void Battle::gamelogic_newTurn(PlayerRole::ePlayerRole newActivePlayer)
{
    // get a copy of all the dice available for this player.
    std::vector<Die> dice = rules.getDice();
    // final set of dice that is going to be used.
    std::vector<Die> finalDice;
    // get the current active player.
    Unit& unit = getUnit(newActivePlayer);
    sf::Int32 diceMax = unit.diceCounter - unit.shockCounter;
    // add the die to the final list
    while(diceMax < dice.size() && dice.size() != 0)
    {
        int r = rand() % dice.size();
        dice.erase(dice.begin() + r);
    }
    for(sf::Int32 i = 0 ; i < unit.freezeCounter && dice.size() != 0 ; i++)
    {
        int r = rand() % dice.size();
        Die d = dice[r];
        dice.erase(dice.begin() + r);
        d.frozen = true;
        finalDice.push_back(d);
    }
    for(std::vector<Die>::iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        finalDice.push_back(*it); 
    }
    gamelogic_setActiveTurn(newActivePlayer, unit.burnCounter, diceMax, unit.freezeCounter, finalDice);
}

////////// commands from updater ////


bool Battle::gamelogic_receivedDoneCommand()
{
    // Done command can only be processed when battle is in the following states.
    // .1 PreRoll - If the player has been stunned too much, he might choose not to roll the die.
    // .2 DiceRolledAbilityUsed - If the player rolled and has use a ability.
    if(_battleState != PreRoll && _battleState != AbilityUsed)
    {
        return false;
    }
    gamelogic_endTurn();
    if(!gamelogic_checkGameEnd())
    {
        gamelogic_newTurn(PlayerRole::opponentOf(_currentPlayer));
        gamelogic_checkGameEnd();
    }
    return true;
}

bool Battle::gamelogic_receivedRollCommand(const std::vector<sf::Int32>& diceId)
{
    // Roll Command can only be processed when battle is in the following states.
    // .1 PreRoll - No dice id is required. The number of dice rolled will be equal to the player's diceCounter - freezeCounter.
    // .2 DiceRolledAbilityUsed - The dice represent the dice that the player choose to roll. The other dice will not be modified/rolled.
    if(_battleState != PreRoll && _battleState != AbilityUsed || diceId.size() == 0)
    {
        return false;
    }
  
    std::vector<Die> dice;
    // get all the dice from the rules for all these id.
    for(sf::Int32 i = 0 ; i < diceId.size(); i++)
    {
        bool found = false;
        //find the current dice
        for(std::vector<Die>::iterator it = _currentDice.begin() ; it != _currentDice.end() ; ++it)
        {
            if(diceId[i] == (*it).id)
            {
                if((*it).frozen && (*it).rolled)
                {
                    return false;
                }
                dice.push_back(*it);
                found = true;
                break;
            }
        }
        if(!found)
        {
            return false;
        }
    }
    // roll all the dice
    for(std::vector<Die>::iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        (*it).roll(); 
    }
    gamelogic_setDiceRolled(dice);
    // set damage taken if turn end because of no valid move.
    bool hasMove = false;
    for(std::vector<Ability>::const_iterator it = rules.getAbilities().begin() ; it != rules.getAbilities().end() ; ++it)
    {
        if((*it).canUseAbility(_currentDice))
        {
            hasMove = true;
            break;
        } 
    }
    if(!hasMove)
    {
        Unit& unit = getUnit(_currentPlayer);
        gamelogic_endTurn(unit.getNoMoveDamage());
        if(!gamelogic_checkGameEnd())
        {
            gamelogic_newTurn(PlayerRole::opponentOf(_currentPlayer));
            // new turn also may have end game due to burn damage
            gamelogic_checkGameEnd();
        }
    }
    return true;
}

void Battle::gamelogic_newDice(std::vector<Die> dice)
{
    viewer_sendNewDiceMessages(dice);
    // set the current dice
    _currentDice = dice;
}

bool Battle::gamelogic_receivedUseAbilityCommand(const Ability& abilityUsed, const std::vector<sf::Int32>& diceUsed)
{
    // Use Ability can only be processed when battle is in the following states.
    // .1 DiceRolled - Ability can be used.
    // .2 DiceRolledAbilityUsed  - Ability also can be used.
    if(_battleState != DiceRolled)
    {
        return false;
    }
    // make sure the dice exist.
    std::vector<Die> usedDice = findDice(diceUsed);
    // if the dice size is not equals to the size of the id provided, 
    if(usedDice.size() != diceUsed.size())
    {
        return false;
    }
    // make sure that the ability is part of the rule
    if(!rules.containsAbility(abilityUsed))
    {
        return false;
    }
    if(!abilityUsed.canUseAbility(usedDice))
    {
        return false;
    }
    gamelogic_abilityUsed(_currentPlayer, abilityUsed,diceUsed);
    // check if the game ends 
    if(gamelogic_checkGameEnd())
    {
    }
    else
    {
        // if the game haven't ends, check if need to send new set of dice.
        if(_currentDice.size() == 0)
        {
            std::vector<Die> dice = rules.getDice();
            gamelogic_newDice(dice);
        }
    }
    return true;
}

bool Battle::gamelogic_checkGameEnd()
{
    if(_units[PlayerRole::PlayerOne].currentHp <= 0)
    {
        gamelogic_endGame(PlayerRole::PlayerTwo);
        return true;
    }
    else if(_units[PlayerRole::PlayerTwo].currentHp <= 0)
    {
        gamelogic_endGame(PlayerRole::PlayerOne);
        return true;
    }
    return false;
}
