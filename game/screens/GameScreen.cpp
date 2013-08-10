#include "GameScreen.hpp"
#include "GameScreenViewer.hpp"
#include "GameScreenUpdater.hpp"
#include "../logic/GeneralUpdater.hpp"
#include "../Game.hpp"
#include "../logic/Battle.hpp"
#include "../../z_framework/zf_common/debugging.hpp"
#include <iostream>

const int GameScreen::AbilityDisplayed = 7;
const int GameScreen::Ability_X = 100;
const int GameScreen::Ability_Y[] = {120,170,220,270,320,370,420};
const int GameScreen::AbilityOffScreen_Y[] = {500,550,600,650,700,750,800};

const int GameScreen::DieX = 26;
const int GameScreen::DieY[] = {30, 90, 150, 210, 270, 330, 390};

const int GameScreen::UnitPositionX[] = {100, 370};
const int GameScreen::UnitPositionY[] = {5, 5};

const sf::FloatRect GameScreen::RollButtonSize = sf::FloatRect(0,0,200,200);
const sf::FloatRect GameScreen::DoneButtonSize = sf::FloatRect(0,0,200,200);

const sf::Vector2f GameScreen::RollButtonPosition = sf::Vector2f(135,150);
const sf::Vector2f GameScreen::DoneButtonPosition = sf::Vector2f(405,150);

const sf::Vector2f GameScreen::AbilityMoveSpeed = sf::Vector2f(0,1000);
GameScreen::GameScreen(Game& game, Battle& b, PlayerRole::ePlayerRole r, GameViewer& v, GameUpdater& u)
    :Screen(game), _battle(b), _role(r), _viewer(v), _updater(u), _currentState(Empty), _currentPlayer(PlayerRole::PlayerOne)
    ,rollButton(game.assets.gameScreenAssets.rollButtonSelected.createSprite(), game.assets.gameScreenAssets.rollButton.createSprite(), RollButtonSize)
    ,doneButton(game.assets.gameScreenAssets.doneButtonSelected.createSprite(), game.assets.gameScreenAssets.doneButton.createSprite(), DoneButtonSize)
{
    rollButton.setPosition(RollButtonPosition);
    doneButton.setPosition(DoneButtonPosition);
}

GameScreen::~GameScreen()
{
}

void GameScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
    {
        (*it).draw(window,delta);
    }
    for(std::vector<AbilitySprite>::iterator it = _abilitySprites.begin() ; it != _abilitySprites.end() ; ++it)
    {
        (*it).draw(window,delta); 
    }
    for(std::vector<UnitSprite>::iterator it = _units.begin() ; it != _units.end() ; ++it)
    {
        (*it).draw(window,delta); 
    }
    if(_currentState == AbilityUsed)
    {
        doneButton.draw(window, delta);
    }
    if(_currentState == AbilityUsed || _currentState == DiceNotRolled)
    {
        rollButton.draw(window,delta);
    }
}

void GameScreen::freeFirstMessage()
{
    Message* m = messages.front();
    messages.pop();
    // free the actual class
    if(m->type == Message::GameStartMessage)
    {
        DB_GameStartMessage* message = (DB_GameStartMessage*)m;
        delete message;
    }
    else if(m->type == Message::ActiveTurnMessage)
    {
        DB_ActiveTurnMessage* message = (DB_ActiveTurnMessage*)m;
        delete message;
    }
    else if(m->type == Message::AskForActionMessage)
    {
    }
    else if(m->type == Message::DiceRolledResultMessage)
    {
        DB_DiceRolledResultMessage* message = (DB_DiceRolledResultMessage*)m;
        delete message;
    }
    else if(m->type == Message::AbilityUsedMessage)
    {
        DB_AbilityUsedMessage* message = (DB_AbilityUsedMessage*)m;
        delete message;;
    }
    else if(m->type == Message::EndTurnMessage)
    {
        DB_EndTurnMessage* message = (DB_EndTurnMessage*)m;
        delete message;
    }
    else if(m->type == Message::EndGameMessage)
    {
        DB_EndGameMessage* message = (DB_EndGameMessage*)m;
        delete message;
    }
    else if(m->type == Message::SendDoneCommand)
    {
        DB_SendDoneCommand* message = (DB_SendDoneCommand*)m;
        delete message;
    }
    else if(m->type == Message::SendRollCommand)
    {
        DB_SendRollCommand* message = (DB_SendRollCommand*)m;
        delete message;
    }
    else if(m->type == Message::SendUseAbilityCommand)
    {
        DB_SendUseAbilityCommand* message = (DB_SendUseAbilityCommand*)m;
        delete message;
    }
} 

/**
 * Used by GameScreenViewer
 */
void GameScreen::sendMessage(DB_GameStartMessage& message)
{
    messages.push(new DB_GameStartMessage(message));
}
void GameScreen::sendMessage(DB_ActiveTurnMessage& message)
{
    messages.push(new DB_ActiveTurnMessage(message));
}
void GameScreen::sendMessage(DB_AskForActionMessage& message)
{
}
void GameScreen::sendMessage(DB_AbilityUsedMessage& message)
{
    messages.push(new DB_AbilityUsedMessage(message));
}
void GameScreen::sendMessage(DB_DiceRolledResultMessage& message)
{
    messages.push(new DB_DiceRolledResultMessage(message));
}
void GameScreen::sendMessage(DB_EndTurnMessage& message)
{
    messages.push(new DB_EndTurnMessage(message));
}
void GameScreen::sendMessage(DB_EndGameMessage& message)
{
    messages.push(new DB_EndGameMessage(message));
}

////// 

void GameScreen::setDie(Die& die)
{
    for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
    {
        if((*it).id == die.id)
        {
            (*it).actualFace = die.currentFace;
            (*it).setEmpty(false);
            break;
        } 
    }
}

void GameScreen::setDice(std::vector<Die>& dice)
{
    for(std::vector<Die>::iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        setDie(*it); 
    }    
}

void GameScreen::setMatchedAbilities(std::vector<Ability> abilities)
{
    for(int i = 0 ; i < abilities.size(); i++)
    {
        AbilitySprite as = makeAbilitySprite(abilities[i]);
        as.setPosition(sf::Vector2f(Ability_X, AbilityOffScreen_Y[i]));
        as.finalPosition = sf::Vector2f(Ability_X, Ability_Y[i]);
        _abilitySprites.push_back(as);  
    }
}
