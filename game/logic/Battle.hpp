#ifndef _GAME_LOGIC_BATTLE_H_
#define _GAME_LOGIC_BATTLE_H_
#include "Unit.hpp"
class GameViewer;
class Battle
{
public:
    Battle(Unit u1, Unit u2);
    ~Battle();
    void addGameViewer(GameViewer* viewer);
    const Unit& getUnit(PlayerRole::ePlayerRole player);
private:
    
    Unit units[2];
    
    // Store whose turn it is.
    PlayerRole::ePlayerRole currentTurn;
    std::vector<Die> currentDices; 
    std::vector<GameViewer*> viewers;
};
#endif
