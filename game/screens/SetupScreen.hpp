#ifndef _GAME_SCREENS_SETUPSCREEN_H_
#define _GAME_SCREENS_SETUPSCREEN_H_
#include "Screen.hpp"
#include "../constants/GameType.hpp"
#include "../../z_framework/zf_sfml/SpriteGroup.hpp"
#include "../../z_framework/zf_sfml/Button.hpp"
#include "../../z_framework/zf_network/zf_gamesetup/GameSetup.hpp"
#include "../../z_framework/zf_network/zf_gamesetup/GameSetupListener.hpp"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
class SetupScreen : public Screen, public zf::GameSetupListener
{
public:

    static const sf::Vector2f name1Position;
    static const sf::Vector2f name2Position;
    static const sf::Vector2f startButtonPosition;
    static const sf::Vector2f nameOffset;
    static const sf::Vector2f buttonTextOffset;
    static const sf::Vector2f waitingForServerOffset;
    static const sf::Vector2f vsTextPosition;
    static const sf::FloatRect ButtonSize;
    static const int MAX_NAME_SIZE = 12;
    enum ButtonState
    {
        None = 0,
        Hovered = 1,
        Disabled = 2,
        Active = 3,
    };
    enum CurrentSelection 
    {
        Name1,
        Name2,
    };
    /**
     * if the setuptype is local then set is not required.
     * This is probably extremely hackish. ....
     */
    SetupScreen(Game& game, GameType::eGameType st, zf::GameSetup* setup = 0);
    ~SetupScreen();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void textInput(char c);

    void screenEnter();
    void screenExit();

    void gameStarts();
    void joinSuccess(std::string name, std::string role);
    void playerJoined(std::string uniqueId, std::string name, std::string role);
    void playerSwitchRole(std::string uniqueId, std::string name, std::string oldRole, std::string newRole);
    void playerLeft(std::string uniqueId, std::string name, std::string role);


private:
    struct PlayerObj
    {
        std::string uniqueId;
        std::string name;
        std::string role;
    };
    zf::GameSetup* _gameSetup;
    GameType::eGameType setupType;

    zf::SpriteGroup nameBorder1;
    zf::SpriteGroup nameBorder2;
    zf::Button _startButton;

    sf::Text name1Text;
    sf::Text name2Text;
    sf::Text waitingForServerText;
    // text that will not change but need to be displayed.
    std::vector<sf::Text> fixedTexts;
    
    PlayerObj player1;
    PlayerObj player2;
    std::vector<PlayerObj> observers;

    CurrentSelection currentSelection;
    void updateText(sf::Text& text, std::string stringValue);    
    void setCurrentSelection(CurrentSelection cs);    

    void updateButtonState(zf::SpriteGroup& spriteGroup, sf::Vector2f position);

    void removePlayer(PlayerObj player);
    void updatePlayer(PlayerObj player);

    bool _connected;
    float _rejoinTimer;
};
#endif
