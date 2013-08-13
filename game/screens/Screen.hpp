#ifndef _GAME_SCREENS_SCREEN_H_
#define _GAME_SCREENS_SCREEN_H_

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
class Game;
class Connection;
class Screen
{
public:
    Screen(Game& game);
    ~Screen();
    
    virtual void draw(sf::RenderWindow& window, const sf::Time& delta) = 0;
    virtual void update(sf::RenderWindow& window, const sf::Time& delta) = 0;
    virtual void textInput(char c) = 0;
    
    virtual void clientConnected(Connection* connection);
    virtual void clientDisconnected(Connection* connection);
    virtual void serverConnected();
    virtual void serverDisconnected();
    virtual void hostingStarted();
    virtual void hostingStopped();
    virtual void packetReceived(sf::Packet& packet, Connection* connection);
    virtual void packetReceivedFromServer(sf::Packet& packet);
protected:
    
    Game& _game;
        

};
#endif
