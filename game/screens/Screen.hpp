#ifndef _GAME_SCREENS_SCREEN_H_
#define _GAME_SCREENS_SCREEN_H_
#include "../../z_framework/zf_network/ConnectionListener.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
class Game;
class Screen : public zf::ConnectionListener
{
public:
    Screen(Game& game);
    ~Screen();
    
    virtual void draw(sf::RenderWindow& window, const sf::Time& delta) = 0;
    virtual void update(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput) = 0;
    virtual void textInput(char c) = 0;
    virtual void screenEnter();
    virtual void screenExit();
    
    virtual void clientConnected(zf::Connection* connection);
    virtual void clientDisconnected(zf::Connection* connection);
    virtual void serverStarted();
    virtual void serverStopped();
    virtual void serverConnected();
    virtual void serverDisconnected();

    virtual void nameInUsed();
    virtual void nameVerified(std::string name);
    virtual void clientVerified(zf::Connection* connection);

    /**
     * Defines the state of the screen. Currently only Exited is used. THe others are states
     * that can be used by child
     */
    enum ScreenState
    {
        Setup, // the preparation state before the screen is entering.
        Entering, // The components of the screen is entering in.
        Active, // The screen is active and ready.
        Exiting, // The screen is exiting
        Exited, // The screen has exited and is ready to be disposed.
    };

    ScreenState screenState;
protected:
    
    Game& _game;
        

};
#endif
