#include "GeneralUpdater.hpp"
GeneralUpdater::GeneralUpdater(PlayerRole::ePlayerRole role)
    :GameUpdater(role)
{
}

bool GeneralUpdater::isConnected()
{
    return connected;
}

void GeneralUpdater::setConnected(bool connected)
{
    this->connected = connected;
}

Message* GeneralUpdater::popNextMessage()
{
    if(messages.empty())
    {
        return 0;
    }
    Message* m = messages.front();
    messages.pop();
    return m;
}

void GeneralUpdater::pushMessage(Message* message)
{
    messages.push(message);
}
