#include "Screen.hpp"
#include "../Game.hpp"

Screen::Screen(Game& game)
    :_game(game), screenState(Setup)
{
}
Screen::~Screen()
{
}
void Screen::clientConnected(zf::Connection* connection)
{
}
void Screen::clientDisconnected(zf::Connection* connection)
{
}
void Screen::serverStarted()
{
}
void Screen::serverStopped()
{
}
void Screen::serverConnected()
{
}
void Screen::serverDisconnected()
{
}
void Screen::nameInUsed()
{
}
void Screen::nameVerified(std::string name)
{
}
void Screen::clientVerified(zf::Connection* connection)
{
}
void Screen::screenEnter()
{
    screenState = Active;
}

void Screen::screenExit()
{
    screenState = Exited;
}
