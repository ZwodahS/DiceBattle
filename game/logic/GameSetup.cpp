#include "GameSetup.hpp"

GameSetup::GameSetup()
    :localRole(PlayerRole::Both), isHosting(false)
{
}

void GameSetup::removeConnection(Connection* connection)
{
    for(std::vector<Connection*>::iterator it = connectedClients.begin() ; it != connectedClients.end() ; )
    {    
        if(connection == *it)
        {
            it = connectedClients.erase(it);
            continue;
        }
        ++it;
    }
}
