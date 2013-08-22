#include "GameScreen.hpp"
#include "GameScreenViewer.hpp"
#include "GameScreenUpdater.hpp"
#include "../logic/GeneralUpdater.hpp"
#include "../Game.hpp"
#include "../logic/Battle.hpp"
#include "../../z_framework/zf_common/debugging.hpp"
#include <iostream>

void GameScreen::removeMessageUntilType(Message::MessageType type)
{
    while(messages.size() != 0)
    {
        Message* m = messages.front();
        if(m->type != type)
        {
            freeFirstMessage();
        }
        else
        {
            break;
        }
    }
}

void GameScreen::update(sf::RenderWindow& window, const sf::Time& delta)
{
    zf::Mouse& mouse = _game.mouse;
    sf::Vector2i mousePosition = mouse.getPosition(window);
    _animator.update(window,delta);
    if(_currentState == Empty)
    {
        update_empty(window,delta);
    }    
    else if(_currentState == AnimatingIn)
    {
        update_animatingIn(window,delta);
    }
    else if(_currentState == GameReady)
    {
        update_gameReady(window,delta);
    }
    else if(_currentState == DiceIn)
    {
        update_diceIn(window,delta);
    }
    else if(_currentState == DiceNotRolled)
    {
        update_diceNotRolled(window,delta);
    }
    else if(_currentState == DiceRolling)
    {
        update_diceRolling(window,delta);
    }
    else if(_currentState == DiceRolled)
    {
        update_diceRolled(window,delta);
    }
    else if(_currentState == AnimatingAbilityUsed)
    {
        update_animatingAbilityUsed(window,delta);
    }
    else if(_currentState == AbilityUsed)
    {
        update_abilityUsed(window,delta);
    }
    else if(_currentState == AnimatingTurnEnds)
    {
        update_animatingTurnEnds(window,delta);
    }
    else if(_currentState == GameEnding)
    {
        update_gameEnding(window,delta);
    }
    else if(_currentState == GameEnd)
    {
        update_gameEnd(window,delta);
    }
    if(_game.isFocused)
    {
        rollButton.updateSelection(sf::Vector2f(mousePosition.x, mousePosition.y));
        doneButton.updateSelection(sf::Vector2f(mousePosition.x, mousePosition.y));
    }
    for(std::vector<AbilitySprite>::iterator it = _abilitySprites.begin() ; it != _abilitySprites.end() ; ++it)
    {
        (*it).update(window,delta); 
    }
}

void GameScreen::update_empty(sf::RenderWindow& window, const sf::Time& delta)
{
    DB_GameStartMessage* startGameMessage = 0;
    // remove all messages other than DB_GameStartMessage
    removeMessageUntilType(Message::GameStartMessage);
    if(messages.size() != 0)
    {
        startGameMessage = (DB_GameStartMessage*)messages.front();
    }
    if(startGameMessage != 0)
    {
        // The message stores a copy of the unit object. In this case, I want the most updated unit.
        // Get it from the battle object instead.
        UnitSprite u1 = makeUnitSprite(_battle.getUnit(PlayerRole::PlayerOne));
        u1.setPosition(sf::Vector2f(UnitPositionX[0], UnitPositionY[0]) + sf::Vector2f(0,-200));
        UnitSprite u2 = makeUnitSprite(_battle.getUnit(PlayerRole::PlayerTwo));
        u2.setPosition(sf::Vector2f(UnitPositionX[1], UnitPositionY[1]) + sf::Vector2f(0,-200));
        _units.push_back(u1);
        _units.push_back(u2);
        _animator.moveReferenceTo(_units[0], sf::Vector2f(UnitPositionX[0], UnitPositionY[0]), 1);
        _animator.moveReferenceTo(_units[1], sf::Vector2f(UnitPositionX[1], UnitPositionY[1]), 1);
        _animationTimer1 = 2;
        _currentState = AnimatingIn;
        messages.pop();
        delete startGameMessage;
    }
}
void GameScreen::update_animatingIn(sf::RenderWindow& window, const sf::Time& delta)
{
    _animationTimer1 -= delta.asSeconds();
    if(_animationTimer1 <= 0)
    {
        _currentState = GameReady;
    }
}

void GameScreen::update_gameReady(sf::RenderWindow& window, const sf::Time& delta)
{
    DB_ActiveTurnMessage* message = 0;
    removeMessageUntilType(Message::ActiveTurnMessage);
    if(messages.size() != 0)
    {
        message = (DB_ActiveTurnMessage*)messages.front();
    }
    if(message != 0)
    {
        messages.pop();
        update_processMessage(message);
        delete message;
    }
}

void GameScreen::update_diceIn(sf::RenderWindow& window, const sf::Time& delta)
{
    _animationTimer1 -= delta.asSeconds();
    if(_animationTimer1 <= 0)
    {
        _currentState = DiceNotRolled;
    }
}

void GameScreen::update_diceNotRolled(sf::RenderWindow& window, const sf::Time& delta)
{
    // check if this gamescreen role is the current role
    if(_role == _battle.currentPlayer || _role == PlayerRole::Both)
    {
        // if this screen is the active player, check for inputs
        zf::Mouse& mouse = _game.mouse;
        sf::Vector2i position = mouse.getPosition(window);
        if(_game.isFocused && _game.mouse.left.thisReleased)
        {
            if(rollButton.clickBound.contains(sf::Vector2f(position.x, position.y)))
            {
                std::vector<sf::Int32> diceRolled;
                for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
                {
                    diceRolled.push_back((*it).die.id); 
                }
                _updater.pushMessage(new DB_SendRollCommand(diceRolled));
            }
        }
    }
    DB_DiceRolledResultMessage* message = 0;
    removeMessageUntilType(Message::DiceRolledResultMessage);
    if(messages.size() != 0)
    {
        message = (DB_DiceRolledResultMessage*)messages.front();
        messages.pop();
        update_processMessage(message);
        delete message;
    }
}

void GameScreen::update_diceRolling(sf::RenderWindow& window, const sf::Time& delta)
{
    _animationTimer1 -= delta.asSeconds();
    if(_animationTimer1 <= 0)
    {
        _currentState = DiceRolled;
        for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
        {
            (*it).setRandom(false); 
        }
        std::vector<Die> rolledDice = getCurrentDice();
        std::vector<Ability> matchedAbilities = _battle.rules.matchAbilities(rolledDice, AbilityDisplayed);
        setMatchedAbilities(matchedAbilities);
        _animationTimer1 = 1;
    }
}
void GameScreen::update_diceRolled(sf::RenderWindow& window, const sf::Time& delta)
{
    if(_role == _battle.currentPlayer || _role == PlayerRole::Both)
    {
        zf::Mouse& mouse = _game.mouse;
        sf::Vector2i mousePos = mouse.getPosition(window);
        sf::Vector2f mousePosF(mousePos.x,mousePos.y);
        // find out if the player select any 
        if(_game.isFocused && mouse.left.thisReleased)
        {
            DieSprite* clickedDieSprite = getDieSprite(mousePosF);
            if(clickedDieSprite != 0)
            {
                clickedDieSprite->toggleSelection();
                std::vector<Die> rolledDice = getCurrentDice();
                std::vector<Die> selectedDice = getSelectedDice();
                std::vector<Ability> matchedAbilities = _battle.rules.matchAbilities(rolledDice, selectedDice, AbilityDisplayed);
                setMatchedAbilities(matchedAbilities);
            }
            else
            {
                // check if any of the ability has been clicked.
                for(std::vector<AbilitySprite>::iterator it = _abilitySprites.begin() ; it != _abilitySprites.end() ; ++it)
                {
                    if((*it).clickBound.contains(mousePosF))
                    {
                        // Right now, I will just check a few things to decide how to send.
                        std::vector<Die> selectedDice = getSelectedDice();
                        Ability& ability = (*it).ability;
                        // if the ability can be cast using the selectedDice, then send the minimum subset of selected 
                        if(ability.canUseAbility(selectedDice))
                        {
                            std::vector<Die> matchedDice = ability.matchDice(selectedDice);
                            _updater.pushMessage(new DB_SendUseAbilityCommand(ability, matchedDice));
                        } 
                        else
                        {
                            // if cannot , try to do a match using the ability function
                            std::vector<Die> rolledDice = _battle.getDice();
                            std::vector<Die> matchedDice = ability.matchDice(rolledDice);
                            if(matchedDice.size() != 0) // shouldn't need this check but put it here anyway.
                            {
                                _updater.pushMessage(new DB_SendUseAbilityCommand(ability, matchedDice));
                            }
                        }
                        break;
                    } 
                }
            }
        }
    }
    if(_animationTimer1 > 0)
    {
        _animationTimer1 -= delta.asSeconds();
    }
    else
    {
        // wait for abiilty used message or end turn message 
        DB_AbilityUsedMessage* abilityUsedMessage = 0;
        DB_EndTurnMessage* endTurnMessage = 0;
        while(messages.size() > 0)
        {
            if(messages.front()->type == Message::AbilityUsedMessage)
            {
                abilityUsedMessage = (DB_AbilityUsedMessage*)messages.front();
                animate_abilityUsed(abilityUsedMessage->abilityUsed);
                animate_diceUsed(abilityUsedMessage->diceUsed);
                _currentState = AnimatingAbilityUsed;
                _animationTimer1 = 2;
                updateUnits();
                break;
            }
            else if(messages.front()->type == Message::EndTurnMessage)
            {
                endTurnMessage = (DB_EndTurnMessage*)messages.front();
                update_processMessage(endTurnMessage);
                updateUnits();
                break;
            }
            else
            {
                freeFirstMessage();
            }
        }
    }
}
void GameScreen::update_animatingAbilityUsed(sf::RenderWindow& window, const sf::Time& delta)
{
    _animationTimer1 -= delta.asSeconds();
    if(_animationTimer1 <= 0)
    {
        DB_AbilityUsedMessage* message = (DB_AbilityUsedMessage*)messages.front();
        _currentState = AbilityUsed;
        _abilitySprites.clear();
        _leavingDiceSprites.clear();
        messages.pop();
        delete message;
    } 
}
void GameScreen::update_abilityUsed(sf::RenderWindow& window, const sf::Time& delta)
{
    if(_role == _battle.currentPlayer || _role == PlayerRole::Both)
    {
        zf::Mouse& mouse = _game.mouse;
        sf::Vector2i position = mouse.getPosition(window);
        if(_game.isFocused && _game.mouse.left.thisReleased)
        {
            // check roll button 
            if(rollButton.clickBound.contains(sf::Vector2f(position.x, position.y)))
            {
                std::vector<sf::Int32> toRoll;
                for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
                {
                    if((*it).selected)
                    {
                        toRoll.push_back((*it).die.id);
                    } 
                }
                _updater.pushMessage(new DB_SendRollCommand(toRoll));
            }
            else if(doneButton.clickBound.contains(sf::Vector2f(position.x, position.y)))
            {
                _updater.pushMessage(new DB_SendDoneCommand());
            }
            else
            {
                DieSprite* ds = getDieSprite(sf::Vector2f(position.x, position.y));
                if(ds != 0)
                {
                    ds->toggleSelection();
                }
            }
        }
    }
    DB_DiceRolledResultMessage* rolledResultMessage = 0;
    DB_EndTurnMessage* endTurnMessage = 0;
    DB_EndGameMessage* endGameMessage = 0;
    DB_NewDiceMessage* newDiceMessage = 0;
    while(messages.size() > 0)
    {
        if(messages.front()->type == Message::EndTurnMessage)
        {
            endTurnMessage = (DB_EndTurnMessage*)messages.front();
            std::cout << "end turn message" << std::endl;
            messages.pop();
            break;
        }
        else if(messages.front()->type == Message::DiceRolledResultMessage)
        {
            rolledResultMessage = (DB_DiceRolledResultMessage*)messages.front();
            std::cout << "dice rolled result message" << std::endl;
            messages.pop();
            break;
        }
        else if(messages.front()->type == Message::EndGameMessage)
        {
            endGameMessage = (DB_EndGameMessage*)messages.front();
            std::cout << "end game message" << std::endl;
            messages.pop();
            break;
        }
        else if(messages.front()->type == Message::NewDiceMessage)
        {
            newDiceMessage = (DB_NewDiceMessage*)messages.front();
            std::cout << "new dice message" << std::endl;
            messages.pop();
            break;
        }
        else
        {
            freeFirstMessage();
        }
    }
    if(rolledResultMessage != 0)
    {
        update_processMessage(rolledResultMessage);
        delete rolledResultMessage;
    }
    else if(endTurnMessage != 0)
    {
        update_processMessage(endTurnMessage);
        delete endTurnMessage;
    }
    else if(endGameMessage != 0)
    {
        update_processMessage(endGameMessage);
        delete endGameMessage;
    }
    else if(newDiceMessage != 0)
    {
        update_processMessage(newDiceMessage);
        delete newDiceMessage;
    }
}
void GameScreen::update_animatingTurnEnds(sf::RenderWindow& window, const sf::Time& delta)
{
    if(_animationTimer1 > 0)
    {
        _animationTimer1 -= delta.asSeconds();
        if(_animationTimer1 <= 0)
        {
            _diceSprites.clear();
            _abilitySprites.clear();
        }
    }
    else
    {
        DB_ActiveTurnMessage* activeTurnMessage = 0;
        DB_EndGameMessage* gameEndMessage = 0;
        // clear ability
        // clear dice
        // check for active turn or game end.
        while(messages.size() > 0)
        {
            if(messages.front()->type == Message::ActiveTurnMessage)
            {
                activeTurnMessage = (DB_ActiveTurnMessage*)messages.front();
                break;
            }
            else if(messages.front()->type == Message::EndGameMessage)
            {
                gameEndMessage = (DB_EndGameMessage*)messages.front();
                break;
            }
            else
            {
                freeFirstMessage();
            }
        }

        if(gameEndMessage != 0)
        {
            update_processMessage(gameEndMessage);
            messages.pop();
            delete gameEndMessage;
        }
        else if(activeTurnMessage != 0)
        {
            update_processMessage(activeTurnMessage);
            messages.pop();
            delete activeTurnMessage;
        }
    }
}
void GameScreen::update_gameEnding(sf::RenderWindow& window, const sf::Time& delta)
{
}
void GameScreen::update_gameEnd(sf::RenderWindow& window, const sf::Time& delta)
{
}







/////////// update process messages ///////////
void GameScreen::update_processMessage(DB_ActiveTurnMessage* message)
{
    // set the active unit 
    _units[_currentPlayer].setActive(false);
    _currentPlayer = message->currentPlayer;
    _units[_currentPlayer].setActive(true);

    // animate the burn damage.
   
    // set the dice 
    update_setDice(message->rollableDice);
    _currentState = DiceIn;
    _animationTimer1 = 1;
}
void GameScreen::update_processMessage(DB_DiceRolledResultMessage* message)
{
    setDice(message->rolledDice);
    for(std::vector<Die>::iterator it = message->rolledDice.begin() ; it != message->rolledDice.end() ; ++it)
    {
        DieSprite* ds = getDieSprite((*it).id);
        if(ds != 0)
        {
            ds->setRandom(true);
        } 
    }
    _currentState = DiceRolling;
    _animationTimer1 = 1;
}

void GameScreen::update_processMessage(DB_EndTurnMessage* message)
{
    for(int i = 0 ; i < _diceSprites.size() ; i++)
    {
        _animator.moveReference(_diceSprites[i], sf::Vector2f(0, 800), 1);
    }    
    for(int i = 0 ; i < _abilitySprites.size() ; i++)
    {
        _abilitySprites[i].finalPosition = sf::Vector2f(Ability_X, AbilityOffScreen_Y[i]);
        _abilitySprites[i].fade = true;
    }
    _currentState = AnimatingTurnEnds;
    _animationTimer1 = 2;
    updateUnits();
}

void GameScreen::update_processMessage(DB_EndGameMessage* message)
{
    std::cout << "end game message" << std::endl;
}

void GameScreen::update_processMessage(DB_NewDiceMessage* message)
{
    std::cout << "processing new dice" << std::endl;
    update_setDice(message->dice);
    _currentState = DiceNotRolled;
}

void GameScreen::update_setDice(std::vector<Die>& dice)
{
    _diceSprites.clear();
    for(std::vector<Die>::iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        DieSprite d = makeDie(*it);
        _diceSprites.push_back(d); 
    }
    for(int i = 0 ; i < _diceSprites.size() ; i++)
    {
        _diceSprites[i].setPosition(sf::Vector2f(DieX, DieY[i]-400));
        _animator.moveReferenceTo(_diceSprites[i], sf::Vector2f(DieX, DieY[i]), 0.5);
    }
}
