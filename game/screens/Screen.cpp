#include "Screen.hpp"
#include "../Game.hpp"

Screen::Screen(Game& game)
    :_game(game)
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
