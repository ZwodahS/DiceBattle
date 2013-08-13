#include "Game.hpp"
#include "screens/Screen.hpp"
#include "screens/SetupScreen.hpp"
#include "screens/GameScreen.hpp"
void Game::clientConnected(Connection* connection)
{
    if(_currentScreen != 0)
    {
        _currentScreen->clientConnected(connection);
    }
}
void Game::clientDisconnected(Connection* connection)
{
    if(_currentScreen != 0)
    {
        _currentScreen->clientDisconnected(connection);
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
void Game::hostingStarted()
{
    if(_currentScreen != 0)
    {
        _currentScreen->hostingStarted();
    }
}
void Game::hostingStopped()
{
    if(_currentScreen != 0)
    {
        _currentScreen->hostingStopped();
    }
}
void Game::packetReceived(sf::Packet& packet, Connection* connection)
{
    sf::Int32 type;
    packet >> type;
    if(type == SetupMessage)
    {
        if(_setupScreen != 0)
        {
            _setupScreen->packetReceived(packet, connection);
        }
    }
    else if(type == GameMessage)
    {
        if(_gameScreen != 0)
        {
            _gameScreen->packetReceived(packet, connection);
        }
    }
}
void Game::packetReceivedFromServer(sf::Packet& packet)
{
    sf::Int32 type;
    packet >> type;
    if(type == SetupMessage)
    {
        if(_setupScreen != 0)
        {
            _setupScreen->packetReceivedFromServer(packet);
        }
    }
    else if(type == GameMessage)
    {
        if(_gameScreen != 0)
        {
            _gameScreen->packetReceivedFromServer(packet);
        }
    }
}
