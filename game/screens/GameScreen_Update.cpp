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
    rollButton.updateSelection(sf::Vector2f(mousePosition.x, mousePosition.y));
    doneButton.updateSelection(sf::Vector2f(mousePosition.x, mousePosition.y));
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
        // set the active unit 
        _units[_currentPlayer].setActive(false);
        _currentPlayer = message->currentPlayer;
        _units[_currentPlayer].setActive(true);

        // animate the burn damage.
        
        // roll in the dice
        _diceSprites.clear();
        for(std::vector<Die>::iterator it = message->rollableDice.begin() ; it != message->rollableDice.end() ; ++it)
        {
            DieSprite d = makeDie(*it);
            _diceSprites.push_back(d);
        }
        // assign the starting position of the dice and roll them in.
        for(int i = 0 ; i < _diceSprites.size() ; i++)
        {
            _diceSprites[i].setPosition(sf::Vector2f(DieX, DieY[i]-400));
            _animator.moveReferenceTo(_diceSprites[i], sf::Vector2f(DieX, DieY[i]), 0.5);
        }
        messages.pop();
        delete message;
        _currentState = DiceIn;
        _animationTimer1 = 1;
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
        if(_game.mouse.left.thisReleased)
        {
            if(rollButton.clickBound.contains(sf::Vector2f(position.x, position.y)))
            {
                std::vector<sf::Int32> diceRolled;
                for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
                {
                    diceRolled.push_back((*it).id); 
                }
                _updater.pushMessage(new DB_SendRollCommand(diceRolled));
            }
        }
    }
    // if not then wait for message 
    DB_DiceRolledResultMessage* message = 0;
    removeMessageUntilType(Message::DiceRolledResultMessage);
    if(messages.size() != 0)
    {
        message = (DB_DiceRolledResultMessage*)messages.front();
        setDice(message->rolledDice);
        for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
        {
            // animate rolling
            (*it).setRandom(true); 
        }
        _currentState = DiceRolling;
        _animationTimer1 = 2;
        messages.pop();
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
        std::vector<Die> rolledDice = _battle.getDice();
        std::vector<Ability> matchedAbilities = _battle.rules.matchAbilities(rolledDice, AbilityDisplayed);
        setMatchedAbilities(matchedAbilities);
    }
}
void GameScreen::update_diceRolled(sf::RenderWindow& window, const sf::Time& delta)
{
    if(_role == _battle.currentPlayer || _role == PlayerRole::Both)
    {
        zf::Mouse& mouse = _game.mouse;
        sf::Vector2i mousePos = mouse.getPosition(window);
        sf::Vector2f mousePosF(mousePos.x,mousePos.y);
        // find out if the player select any dice
        if(mouse.left.thisReleased)
        {
            bool hit = false;
            for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
            {
                if((*it).clickBound.contains(mousePosF))
                {
                    (*it).toggleSelection();
                    hit = true;
                    break;
                }
            }        
            if(hit)
            {
                std::vector<Die> rolledDice = _battle.getDice();
                std::vector<Die> selectedDice = getSelectedDice();
                std::vector<Ability> matchedAbilities = _battle.rules.matchAbilities(rolledDice, selectedDice, AbilityDisplayed);
                setMatchedAbilities(matchedAbilities);
            }
        }
    }
}
void GameScreen::update_animatingAbilityUsed(sf::RenderWindow& window, const sf::Time& delta)
{
}
void GameScreen::update_abilityUsed(sf::RenderWindow& window, const sf::Time& delta)
{
}
void GameScreen::update_animatingTurnEnds(sf::RenderWindow& window, const sf::Time& delta)
{
}
void GameScreen::update_gameEnding(sf::RenderWindow& window, const sf::Time& delta)
{
}
void GameScreen::update_gameEnd(sf::RenderWindow& window, const sf::Time& delta)
{
}
