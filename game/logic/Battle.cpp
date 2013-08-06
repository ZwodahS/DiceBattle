#include "Battle.hpp"
#include "GameViewer.hpp"
#include "GameUpdater.hpp"

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
