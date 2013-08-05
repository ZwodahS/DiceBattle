#include "Battle.hpp"
Battle::Battle(Unit u1, Unit u2)
{
    units[PlayerRole::PlayerOne] = u1;
    units[PlayerRole::PlayerTwo] = u2;
}

Battle::~Battle()
{
}

const Unit& Battle::getUnit(PlayerRole::ePlayerRole p)
{
    return units[p];
}

void Battle::addGameViewer(GameViewer* viewer)
{
    this->viewers.push_back(viewer);
}
