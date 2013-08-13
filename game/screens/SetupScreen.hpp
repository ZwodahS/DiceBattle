#ifndef _GAME_SCREENS_SETUPSCREEN_H_
#define _GAME_SCREENS_SETUPSCREEN_H_
#include "Screen.hpp"
#include "../../z_framework/zf_sfml/SpriteGroup.hpp"
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
class SetupScreen : public Screen
{
public:

    static const sf::Vector2f name1Position;
    static const sf::Vector2f name2Position;
    static const sf::Vector2f ipAddrPosition;
    static const sf::Vector2f joinButtonPosition;
    static const sf::Vector2f hostButtonPosition;
    static const sf::Vector2f nameOffset;
    static const sf::Vector2f buttonTextOffset;

    static const sf::Vector2f vsTextPosition;

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
        IpAddr,
    };

    SetupScreen(Game& game);
    ~SetupScreen();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void textInput(char c);
private:

    sf::Sprite nameBorder1;
    sf::Sprite nameBorder2;
    zf::SpriteGroup joinButton;
    zf::SpriteGroup hostButton;
    sf::Sprite ipAddrBorder;

    sf::Text name1Text;
    sf::Text name2Text;
    sf::Text ipAddr;
    sf::Text joinText;
    sf::Text hostText;

    // text that will not change but need to be displayed.
    std::vector<sf::Text> fixedTexts;
    
    std::string name1;
    std::string name2;
    std::string ipAddrString;

    CurrentSelection currentSelection;
    void updateText(sf::Text& text, std::string stringValue);    
    void setCurrentSelection(CurrentSelection cs);    


    sf::TcpSocket* _currentSocket;
};
#endif
