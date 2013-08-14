#include "Screen.hpp"
#include "../Game.hpp"

Screen::Screen(Game& game)
    :_game(game), screenState(Setup)
{
}
Screen::~Screen()
{
}
void Screen::clientConnected(Connection* connection)
{
}
void Screen::clientDisconnected(Connection* connection)
{
}
void Screen::serverConnected()
{
}
void Screen::serverDisconnected()
{
}
void Screen::hostingStarted()
{
}
void Screen::hostingStopped()
{
}
void Screen::packetReceived(sf::Packet& packet, Connection* connection)
{
}
void Screen::packetReceivedFromServer(sf::Packet& packet)
{
}

void Screen::screenEnter()
{
    screenState = Entering;
}

void Screen::screenExit()
{
    screenState = Exiting;
}
