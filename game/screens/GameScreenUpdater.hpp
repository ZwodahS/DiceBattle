#ifndef _GAME_LOGIC_GAMESCREENUPDATER_H_
#define _GAME_LOGIC_GAMESCREENUPDATER_H_
#include "../logic/GameUpdater.hpp"
class GameScreenUpdater : public GameUpdater
{
public:
    std::vector<Message*> messages;
};
#endif
