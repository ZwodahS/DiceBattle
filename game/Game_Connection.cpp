#include "Game.hpp"

void Game::clientConnected(Connection* connection)
{
    std::cout << "client Connected" << std::endl;
}
void Game::clientDisconnected(Connection* connection)
{
    std::cout << "Client Disconnected" << std::endl;
}
void Game::serverConnected()
{
    std::cout << "Server Connected" << std::endl;
}
void Game::serverDisconnected()
{
    std::cout << "Server Disconnected" << std::endl;
}
void Game::hostingStarted()
{
    std::cout << "Hosting Started" << std::endl;
}
void Game::hostingStopped()
{
    std::cout << "Hosting Stopped" << std::endl;
}
void Game::packetReceived(sf::Packet& packet, Connection* connection)
{
    std::cout << "Packet received" << std::endl;
}
void Game::packetReceivedFromServer(sf::Packet& packet)
{
    std::cout << "Packet Received from server" << std::endl;
}
