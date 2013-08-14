#ifndef _GAME_LOGIC_GAMESETUP_H_
#define _GAME_LOGIC_GAMESETUP_H_
#include "../Connection.hpp"
#include "../constants.hpp"
/**
 * This struct just hold the information for setting up a game.
 * It is just to organize the information. It provide no logic.
 */
struct GameSetup
{
    // This stores the role of the "host".
    PlayerRole::ePlayerRole localRole;

    bool isHosting;
    std::vector<Connection*> connectedClients;

    GameSetup();
    
    void removeConnection(Connection* connection);
};
#endif
