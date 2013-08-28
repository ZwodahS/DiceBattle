#ifndef _GAME_GAME_H_
#define _GAME_GAME_H_

#include "Assets.hpp"
#include "logic/Rules.hpp"
#include "screens/GameScreenViewer.hpp"
#include "logic/GeneralUpdater.hpp"
#include "logic/BattlePacketLayer.hpp"
#include "../z_framework/zf_sfml/Mouse.hpp"
#include "../z_framework/zf_network/Connection.hpp"
#include "../z_framework/zf_network/ConnectionManager.hpp"
#include "../z_framework/zf_network/ConnectionListener.hpp"
#include "../z_framework/zf_network/zf_gamesetup/GameSetup.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#define GAMESETUP_HEADER 4000
class Screen;
class GameScreen;
class MainScreen;
class SetupScreen;
class HelpScreen;
class AbilityScreen;
class Battle;
class Game : public zf::ConnectionListener
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
        zf::ConnectionManager connection;
        Assets assets;
        Rules rules;
        bool isFocused;
        void loadAssets();

        ////// Methods for ConnectionManager to inform the game about connection //////
        void clientConnected(zf::Connection* connection);
        void clientDisconnected(zf::Connection* connection);
        void serverStarted();
        void serverStopped();
        void serverConnected();
        void serverDisconnected();
        void nameInUsed();
        void nameVerified(std::string name);
        void clientVerified(zf::Connection* connection);


        void appendSetupMessageHeader(sf::Packet& packet);
        void appendGameMessageHeader(sf::Packet& packet);

        void setupLocalGame();
        void startLocalGame(std::string player1, std::string player2);

        // this will attempt set up hosting at the port
        // return true if can setup hosting, which will also exit the mainscreen
        bool setupHosting(unsigned short port, std::string name);
        // start the network game as a host
        void startNetworkGame(zf::GameSetup* setup, PlayerRole::ePlayerRole);
        // join the network game as a client
        void joinNetworkGame(zf::GameSetup* setup, PlayerRole::ePlayerRole role);
        /**
         * Attempt to join the server using the name at an address.
         */
        bool setupJoin(std::string name, std::string ipAddr, unsigned short port);
    
        /**
         * Go back to setup from game screen.
         */
        void backToSetup(GameType::eGameType gameType, PlayerRole::ePlayerRole myRole);

        void toggleShowHelp();
        void toggleShowAbilities(Rules& rules);

    private:
        void update(sf::Time& delta);
        void draw(sf::Time& delta);
        void startGame(Battle* battle, PlayerRole::ePlayerRole role); 
        void setupLocalGame(Battle* battle, PlayerRole::ePlayerRole role, std::string player1, std::string player2);
        Screen* _currentScreen;
        Screen* _nextScreen;

        MainScreen* _mainScreen;
        GameScreen* _gameScreen;        
        SetupScreen* _setupScreen;
        HelpScreen* _helpScreen;
        AbilityScreen* _abilityScreen;
        Battle* _currentBattle;

        // Use game object as the connection manager.
        float _waitingReplyTimeout;
        BattlePacketLayer _battlePacketLayer;

        zf::GameSetup* _gameSetup;
        zf::GameSetup* getNewGameSetup(bool isHosting);

        sf::Sprite background;
        bool _showHelp;
        bool _showAbilities;
};


#endif
