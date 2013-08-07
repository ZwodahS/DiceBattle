#include "GameScreen.hpp"
#include "GameScreenViewer.hpp"
#include "GameScreenUpdater.hpp"
#include "../logic/GeneralUpdater.hpp"
#include "../Game.hpp"
#include "../logic/Battle.hpp"
#include <iostream>

GameScreen::GameScreen(Game& game, Battle& b, PlayerRole::ePlayerRole r, GameViewer& v, GameUpdater& u)
    :Screen(game), _battle(b), _role(r), _viewer(v), _updater(u)
{
    for(sf::Int32 i = 0 ; i < 6 ; i++)
    {
        _diceSprites.push_back(makeDie(i));
        _diceSprites[i].setPosition(sf::Vector2f(26, 26 + (i * 60)));
    }
    Unit* unit = new Unit("super long name that throw you off", 100, 6);
    
    _units.push_back(makeUnitSprite(*unit));
    _units[0].setPosition(sf::Vector2f(100,5));
    _units.push_back(makeUnitSprite(*unit));
    _units[1].setPosition(sf::Vector2f(370,5));
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
}

void GameScreen::update(sf::RenderWindow& window, const sf::Time& delta)
{
}

/**
 * Used by GameScreenViewer
 */
void GameScreen::sendMessage(DB_GameStartMessage& message)
{
}
void GameScreen::sendMessage(DB_ActiveTurnMessage& message)
{
}
void GameScreen::sendMessage(DB_AskForActionMessage& message)
{
}
void GameScreen::sendMessage(DB_AbilityUsedMessage& message)
{
}
void GameScreen::sendMessage(DB_DiceRolledResultMessage& message)
{
}
void GameScreen::sendMessage(DB_EndTurnMessage& message)
{
}
void GameScreen::sendMessage(DB_EndGameMessage& message)
{
}



