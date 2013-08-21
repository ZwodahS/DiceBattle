#include "Game.hpp"
#include "screens/Screen.hpp"
#include "screens/SetupScreen.hpp"
#include "screens/GameScreen.hpp"
void Game::clientConnected(zf::Connection* connection)
{
    if(_currentScreen != 0)
    {
        _currentScreen->clientConnected(connection);
    }
}
void Game::clientDisconnected(zf::Connection* connection)
{
    if(_currentScreen != 0)
    {
        _currentScreen->clientDisconnected(connection);
    }
}
void Game::serverStarted()
{
    if(_currentScreen != 0)
    {
        _currentScreen->serverStarted();
    }
}
void Game::serverStopped()
{
    if(_currentScreen != 0)
    {
        _currentScreen->serverStopped();
    }
}
void Game::serverConnected()
{
    if(_currentScreen != 0)
    {
        _currentScreen->serverConnected();
    }
}
void Game::serverDisconnected()
{
    if(_currentScreen != 0)
    {
        _currentScreen->serverDisconnected();
    }
}

void Game::nameInUsed()
{
    std::cout << "Name in used" << std::endl;
}
void Game::nameVerified(std::string name)
{
    //since my name has been verified, try to connect to the gamesetup
    if(_mainScreen != 0)
    {
        zf::GameSetup* gs = new zf::GameSetup(connection.verifiedName, connection, GAMESETUP_HEADER, false);
        _setupScreen = new SetupScreen(*this, SetupScreen::Remote, gs);
        connection.addDownStream(*gs);
        _nextScreen = _setupScreen;
        _currentScreen->screenExit();
        gs->joinServer();
    }
}
void Game::clientVerified(zf::Connection* connection)
{
}
