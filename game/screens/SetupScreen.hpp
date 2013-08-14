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
    static const sf::Vector2f startButtonPosition;
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
    };
    enum SetupType
    {
        Local,
        Host,
        Remote,
    };
    SetupScreen(Game& game, SetupType st);
    ~SetupScreen();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void textInput(char c);
private:
    
    SetupType setupType;

    sf::Sprite nameBorder1;
    sf::Sprite nameBorder2;
    zf::SpriteGroup startButton;

    sf::Text name1Text;
    sf::Text name2Text;
    sf::Text startText;
    // text that will not change but need to be displayed.
    std::vector<sf::Text> fixedTexts;
    
    std::string name1;
    std::string name2;

    CurrentSelection currentSelection;
    void updateText(sf::Text& text, std::string stringValue);    
    void setCurrentSelection(CurrentSelection cs);    

};
#endif
