#include "SetupScreen.hpp"
#include "../Game.hpp"
const sf::Vector2f SetupScreen::name1Position = sf::Vector2f(50, 200);
const sf::Vector2f SetupScreen::name2Position = sf::Vector2f(390, 200);
const sf::Vector2f SetupScreen::nameOffset = sf::Vector2f(10,0);
const sf::Vector2f SetupScreen::startButtonPosition = sf::Vector2f(270, 400);
const sf::Vector2f SetupScreen::buttonTextOffset = sf::Vector2f(20,0);
const sf::Vector2f SetupScreen::vsTextPosition = sf::Vector2f(300, 200);
SetupScreen::SetupScreen(Game& game, SetupType st)
    :Screen(game), setupType(st), name1Text("Player", game.assets.gameScreenAssets.abilityFont, 20), name2Text("Opponent", game.assets.gameScreenAssets.abilityFont, 20)
    , currentSelection(Name1), startText("Start", game.assets.gameScreenAssets.abilityFont, 20)
{
    // name and the name box
    nameBorder1 = game.assets.setupScreenAssets.nameBox.createSprite();
    nameBorder1.setPosition(name1Position);
    name1Text.setPosition(name1Position + nameOffset);
    name1Text.setColor(sf::Color(0,0,0));
    nameBorder2 = game.assets.setupScreenAssets.nameBox.createSprite();
    nameBorder2.setPosition(name2Position);
    name2Text.setPosition(name2Position + nameOffset);
    name2Text.setColor(sf::Color(0,0,0));

    std::vector<sf::Sprite> startButtonSprites;
    for(int i = 0 ; i < 4 ; i++)
    {
        startButtonSprites.push_back(game.assets.setupScreenAssets.startButton.createSprite());
    }
    startButtonSprites[None].setColor(sf::Color(140,70,40));
    startButtonSprites[Hovered].setColor(sf::Color(200,130,90));
    startButtonSprites[Disabled].setColor(sf::Color(160,140,130));
    startButtonSprites[Active].setColor(sf::Color(245,100,25));
    startButton = zf::SpriteGroup(startButtonSprites);
    startButton.setPosition(startButtonPosition);
    startText.setPosition(startButtonPosition+buttonTextOffset);
    startText.setColor(sf::Color::White);
// VS TEXT    
    sf::Text tmp("VS", game.assets.gameScreenAssets.abilityFont, 40);
    tmp.setPosition(vsTextPosition);
    fixedTexts.push_back(tmp);

    name1 = "Player";
    name2 = "Opponent";
    setCurrentSelection(Name1);
}

SetupScreen::~SetupScreen()
{
}

void SetupScreen::textInput(char c)
{
    if(setupType != Local)
    {
        return;
    }
    sf::Text& text = currentSelection == Name1 ? name1Text : name2Text;
    std::string& value = currentSelection == Name1 ? name1 : name2;
    if(c >= 32 && c < 127)
    {
        if(value == " ")
        {
            value = c;
        }
        else
        {
            value += c;
        }
        updateText(text, value);
    }
    // backspace
    else if(c == 8)
    {
        if(value == " ")
        {
            // do nothing
        }
        else if(value.length() == 1)
        {
            value = " ";
        }
        else
        {
            value = value.substr(0, value.length() - 1);
        }
        updateText(text, value);
    }
}

void SetupScreen::setCurrentSelection(CurrentSelection cs)
{
    if(currentSelection == Name1)
    {
        nameBorder1.setColor(sf::Color::White);
    }
    else if(currentSelection == Name2)
    {
        nameBorder2.setColor(sf::Color::White);
    }
    currentSelection = cs;
    if(currentSelection == Name1)
    {
        nameBorder1.setColor(sf::Color(220,220,100));
    }
    else if(currentSelection == Name2)
    {
        nameBorder2.setColor(sf::Color(220,220,100));
    }
}

void SetupScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    window.draw(nameBorder1);
    window.draw(nameBorder2);
    window.draw(name1Text);
    window.draw(name2Text);
    for(std::vector<sf::Text>::iterator it = fixedTexts.begin() ; it != fixedTexts.end() ; ++it)
    {
        window.draw(*it); 
    }
    startButton.draw(window, delta);
    window.draw(startText);
}

void SetupScreen::update(sf::RenderWindow& window, const sf::Time& delta)
{
    // handles input
    if(_game.isFocused && screenState == Screen::Active)
    {
        zf::Mouse& mouse = _game.mouse;
        sf::Vector2i mousePos = mouse.getPosition(window);
        sf::Vector2f mousePosF = sf::Vector2f(mousePos.x,mousePos.y);
        if(mouse.left.thisReleased)
        {
            if(nameBorder1.getGlobalBounds().contains(mousePosF))
            {
                setCurrentSelection(Name1);
            }
            else if(nameBorder2.getGlobalBounds().contains(mousePosF))
            {
                setCurrentSelection(Name2);
            }
            else if(startButton.bound.contains(mousePosF))
            {
                _game.startLocalGame(name1, name2);                
            }
        }
        else
        {
            updateButtonState(startButton, mousePosF);
        }
    }

}
void SetupScreen::updateText(sf::Text& text, std::string stringValue)
{
    // this is necessary for a bug in SFML that if you try to free a sf::Text with empty string, it will cause a segmentation fault.
    if(stringValue == "")
    {
        text.setString(" ");
    }
    else
    {
        text.setString(stringValue);
    }
}

void SetupScreen::screenEnter()
{
    Screen::screenState = Screen::Active;
}

void SetupScreen::screenExit()
{
    Screen::screenState = Screen::Exited;
}

void SetupScreen::updateButtonState(zf::SpriteGroup& spriteGroup, sf::Vector2f position)
{
    if(spriteGroup.bound.contains(position))
    {
        spriteGroup.setState(Hovered); 
    }
    else
    {
        spriteGroup.setState(None);
    }
}
