#ifndef _GAME_LOGIC_GENERALUPDATER_H_
#define _GAME_LOGIC_GENERALUPDATER_H_
#include "../messages/g_messages.hpp"
#include "GameUpdater.hpp"
#include <queue>
class GeneralUpdater : public GameUpdater
{
public:
    GeneralUpdater(PlayerRole::ePlayerRole role);

    bool isConnected();
    void setConnected(bool connected);
    Message* popNextMessage();
    void pushMessage(Message* message);

    std::queue<Message*> messages;

    bool connected;
};
#endif
