#ifndef _GAME_LOGIC_BATTLESERVER_H_
#define _GAME_LOGIC_BATTLESERVER_H_
class BattleServer
{
public:
    virtual bool isConnected() = 0;

    virtual Message* popNextMessage() = 0;
};
#endif
