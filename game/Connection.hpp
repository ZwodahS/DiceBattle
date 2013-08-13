#ifndef _GAME_CONNECTION_H_
#define _GAME_CONNECTION_H_
/** 
 * Connection will not be incharge of freeing the socket. That is done in the connection manager.
 * This allow the connection object to be pass around as value.
 */
#include "constants/PlayerRole.hpp"
#include <SFML/Network.hpp>
struct Connection
{
    Connection();
    ~Connection();
    std::string name;
    sf::TcpSocket socket;
    PlayerRole::ePlayerRole role;
};
#endif
