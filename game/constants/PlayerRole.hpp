#ifndef _GAME_CONSTANTS_PLAYERROLE
#define _GAME_CONSTANTS_PLAYERROLE
#include <SFML/Network.hpp>
namespace PlayerRole
{
    /**
     * This is used for defining the role of the player as well as the viewer.
     * When using this for Player, the allowed role is PlayerOne and PlayerTwo.
     * WHen using tihs for Viewer, the allowed role is all 5. 
     */
    enum ePlayerRole
    {
        PlayerOne = 0,
        PlayerTwo = 1,
        Observer = 2,
        // This client is both player one and player two
        // This is used for local player.
        Both = 3,
        // Placeholder
        None = 4,
    };

    sf::Int32 toInt(ePlayerRole role);
    ePlayerRole toPlayerRole(sf::Int32);
    ePlayerRole randomPlayer();
    ePlayerRole opponentOf(ePlayerRole player);
}

sf::Packet& operator << (sf::Packet& packet, const PlayerRole::ePlayerRole& message);
sf::Packet& operator >> (sf::Packet& packet, PlayerRole::ePlayerRole& message);
#endif
