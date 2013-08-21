#include "GameScreen.hpp"
#include "../Game.hpp"
#include "../logic/Battle.hpp"
#include "../../z_framework/zf_common/debugging.hpp"
#include <iostream>

const int GameScreen::AbilityDisplayed = 7;
const int GameScreen::Ability_X = 100;
const int GameScreen::Ability_Y[] = {120,170,220,270,320,370,420};
const int GameScreen::AbilityOffScreen_Y[] = {600,650,700,750,800,850,900};

const int GameScreen::DieX = 26;
const int GameScreen::DieY[] = {30, 90, 150, 210, 270, 330, 390};

const int GameScreen::UnitPositionX[] = {100, 370};
const int GameScreen::UnitPositionY[] = {5, 5};

const sf::FloatRect GameScreen::RollButtonSize = sf::FloatRect(0,0,200,200);
const sf::FloatRect GameScreen::DoneButtonSize = sf::FloatRect(0,0,200,200);

const sf::Vector2f GameScreen::RollButtonPosition = sf::Vector2f(135,150);
const sf::Vector2f GameScreen::DoneButtonPosition = sf::Vector2f(405,150);

const sf::Vector2f GameScreen::AbilityMoveSpeed = sf::Vector2f(0,1200);
const float GameScreen::FadeSpeed = 400;
GameScreen::GameScreen(Game& game, Battle& b, PlayerRole::ePlayerRole r)
    :Screen(game), _battle(b), _role(r), _currentState(Empty), _currentPlayer(PlayerRole::PlayerOne)
    ,rollButton(game.assets.gameScreenAssets.rollButtonSelected.createSprite(), game.assets.gameScreenAssets.rollButton.createSprite(), RollButtonSize)
    ,doneButton(game.assets.gameScreenAssets.doneButtonSelected.createSprite(), game.assets.gameScreenAssets.doneButton.createSprite(), DoneButtonSize)
    ,_updater(r), _viewer(r, *this)
{
    rollButton.setPosition(RollButtonPosition);
    doneButton.setPosition(DoneButtonPosition);
    _battle.addGameViewer(&_viewer);
    _battle.addGameUpdater(&_updater);
}

GameScreen::~GameScreen()
{
    _battle.removeGameViewer(&_viewer);
    _battle.removeGameUpdater(&_updater);
}

void GameScreen::textInput(char c)
{

}

void GameScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    for(std::vector<DieSprite>::iterator it = _leavingDiceSprites.begin() ; it != _leavingDiceSprites.end() ; ++it)
    {
        (*it).draw(window,delta); 
    }
    for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
    {
        (*it).draw(window,delta);
    }
    for(std::vector<UnitSprite>::iterator it = _units.begin() ; it != _units.end() ; ++it)
    {
        (*it).draw(window,delta); 
    }
    for(std::vector<AbilitySprite>::iterator it = _abilitySprites.begin() ; it != _abilitySprites.end() ; ++it)
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
        delete message;
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
    std::cout << "GameScreen.cpp : 137 " << std::endl;
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
void GameScreen::sendMessage(DB_NewDiceMessage& message)
{
    messages.push(new DB_NewDiceMessage(message));
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
        if((*it).die.id == die.id)
        {
            (*it).setDie(die);
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

std::vector<Die> GameScreen::getSelectedDice()
{
    std::vector<sf::Int32> dieIds;
    for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
    {
        if((*it).selected)
        {
            dieIds.push_back((*it).die.id);
        } 
    }
    return _battle.findDice(dieIds);
}

std::vector<Die> GameScreen::getCurrentDice()
{
    std::vector<Die> dice;
    for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
    {
        dice.push_back((*it).die); 
    }
    return dice;
}

void GameScreen::setMatchedAbilities(std::vector<Ability> abilities)
{
    // list of ability sprite to keep
    std::vector<AbilitySprite> keep;
    // for every abilities in the list.
    for(int i = 0 ; i < abilities.size(); i++)
    {
        // check if the ability sprite already exist. 
        // If the ability sprite already exist, then just move it to the correct position 
        if(hasAbilitySprite(abilities[i]))
        {
            AbilitySprite as = getAndRemoveAbilitySprite(abilities[i]);
            as.finalPosition = sf::Vector2f(Ability_X, Ability_Y[i]);
            as.moveSpeed = AbilityMoveSpeed;
            keep.push_back(as);
        }
        else
        {
            // if the Ability sprite do not exist, then create it
            AbilitySprite as = makeAbilitySprite(abilities[i]);
            as.setPosition(sf::Vector2f(Ability_X, AbilityOffScreen_Y[i]));
            as.finalPosition = sf::Vector2f(Ability_X, Ability_Y[i]);
            as.moveSpeed = AbilityMoveSpeed;
            keep.push_back(as);  
        }
    }
    // the list now contains the list of ability sprites that do not match the new list. 
    // Just clear them for now. In the future, I might want to fade them out.
    _abilitySprites.clear();
    _abilitySprites = keep;
}
bool GameScreen::hasAbilitySprite(Ability a)
{
    for(std::vector<AbilitySprite>::iterator it = _abilitySprites.begin() ; it != _abilitySprites.end() ; ++it)
    {
        if((*it).ability == a)
        {
            return true;
        } 
    }
    return false;
}
GameScreen::AbilitySprite GameScreen::getAndRemoveAbilitySprite(Ability a)
{
    for(std::vector<AbilitySprite>::iterator it = _abilitySprites.begin() ; it != _abilitySprites.end() ; ++it)
    {
        if((*it).ability == a)
        {
            AbilitySprite as = *it;
            _abilitySprites.erase(it);
            return as;
        } 
    }
    return makeAbilitySprite(a);
}

bool GameScreen::hasDieSprite(sf::Int32 i)
{
    for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
    {
        if((*it).die.id == i)
        {
            return true;
        } 
    }
    return false;
}

GameScreen::DieSprite GameScreen::getAndRemoveDieSprite(sf::Int32 i)
{
    for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
    {
        if((*it).die.id == i)
        {
            DieSprite ds = *it;
            _diceSprites.erase(it);
            return ds;
        } 
    }
    Die d;
    return makeDie(d);
}

void GameScreen::animate_abilityUsed(Ability& ability)
{
    std::vector<AbilitySprite> tmp;
    if(hasAbilitySprite(ability))
    {
        AbilitySprite as = getAndRemoveAbilitySprite(ability);
        as.finalPosition = sf::Vector2f(Ability_X, Ability_Y[0] - 40);
        sf::Vector2f tmpPos = as.getPosition();
        // the final position of this is always less than the current position relative to top left.
        // Since the move speed needs to be positive, speed = current - final
        as.moveSpeed = tmpPos - as.finalPosition;
        tmp.push_back(as);
    }
    else
    {
        AbilitySprite as = makeAbilitySprite(ability);
        as.setPosition(sf::Vector2f(Ability_X, AbilityOffScreen_Y[0]));
        as.finalPosition = sf::Vector2f(Ability_X, Ability_Y[0] - 40);
        tmp.push_back(as);
    }
    int i = 0;
    for(std::vector<AbilitySprite>::iterator it = _abilitySprites.begin() ; it != _abilitySprites.end() ; ++it)
    {
        (*it).finalPosition = sf::Vector2f(Ability_X, AbilityOffScreen_Y[i]); 
        i++;
        (*it).fade = true;
        sf::Vector2f currentPosition = (*it).getPosition();
        // the final position is always "more" than the current position relative to top left
        (*it).moveSpeed = ((*it).finalPosition - currentPosition);
    }
    _abilitySprites.push_back(tmp[0]);
}

void GameScreen::animate_diceUsed(std::vector<sf::Int32> dice)
{
    for(std::vector<sf::Int32>::iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        if(hasDieSprite(*it))
        {
            DieSprite ds = getAndRemoveDieSprite(*it);
            _leavingDiceSprites.push_back(ds);
        } 
    }
    for(std::vector<DieSprite>::iterator it = _leavingDiceSprites.begin() ; it != _leavingDiceSprites.end() ; ++it)
    {
        _animator.moveReference(*it, sf::Vector2f(0,200), 2);
        _animator.fadeReference(*it, 255 , 0 , 1);
    }
    for(int i = 0 ; i < _diceSprites.size() ; i++)
    {
        _animator.moveReferenceTo(_diceSprites[i], sf::Vector2f(DieX, DieY[i]), 1);
    }
}

GameScreen::DieSprite* GameScreen::getDieSprite(sf::Vector2f mousePosF)
{
    for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
    {
        if((*it).clickBound.contains(mousePosF))
        {
            return &(*it);
        }
    }
    return 0;    
}

GameScreen::DieSprite* GameScreen::getDieSprite(const sf::Int32 id)
{
    for(std::vector<DieSprite>::iterator it = _diceSprites.begin() ; it != _diceSprites.end() ; ++it)
    {
        if((*it).die.id == id)
        {
            return &(*it);
        } 
    }
    return 0;
}

void GameScreen::updateUnits()
{
    _units[PlayerRole::PlayerOne].updateData();
    _units[PlayerRole::PlayerTwo].updateData();
}

