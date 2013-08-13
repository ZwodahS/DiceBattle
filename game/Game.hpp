#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_

#include "Assets.hpp"
#include "logic/Rules.hpp"
#include "screens/GameScreenViewer.hpp"
#include "logic/GeneralUpdater.hpp"
#include "../z_framework/zf_sfml/Mouse.hpp"
#include "Connection.hpp"
#include "ConnectionManager.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class Screen;
class GameScreen;
class SetupScreen;
class Battle;
class Game
{
    public:
        static const sf::Int32 SetupMessage = 1111;
        static const sf::Int32 GameMessage = 2222;
        Game();
        ~Game();
        void run(); 


        const sf::Int32 width;
        const sf::Int32 height;
        std::string title;
        sf::RenderWindow window; 
        zf::Mouse mouse;
        ConnectionManager connection;
        Assets assets;
        Rules rules;
        bool isFocused;
        void loadAssets();

        ////// Methods for ConnectionManager to inform the game about connection //////
        void clientConnected(Connection* connection);
        void clientDisconnected(Connection* connection);
        void serverConnected();
        void serverDisconnected();
        void hostingStarted();
        void hostingStopped();
        void packetReceived(sf::Packet& packet, Connection* connection);
        void packetReceivedFromServer(sf::Packet& packet);


        void appendSetupMessageHeader(sf::Packet& packet);
        void appendGameMessageHeader(sf::Packet& packet);
    private:
        void update(sf::Time& delta);
        void draw(sf::Time& delta);
        void startGame(Battle* battle, PlayerRole::ePlayerRole role); 
        void startLocalGame(Battle* battle, PlayerRole::ePlayerRole role, std::string player1, std::string player2);
        Screen* _currentScreen;
        GameScreen* _gameScreen;        
        SetupScreen* _setupScreen;
        Battle* _currentBattle;
        GameScreenViewer* _viewer;
        GeneralUpdater* _updater;

        // Use game object as the connection manager.

};


#endif

