#include "SetupScreen.hpp"
#include "../Game.hpp"
const sf::Vector2f SetupScreen::name1Position = sf::Vector2f(50, 200);
const sf::Vector2f SetupScreen::name2Position = sf::Vector2f(390, 200);
const sf::Vector2f SetupScreen::nameOffset = sf::Vector2f(10,0);
const sf::Vector2f SetupScreen::ipAddrPosition = sf::Vector2f(150, 300);
const sf::Vector2f SetupScreen::joinButtonPosition = sf::Vector2f(370, 300);
const sf::Vector2f SetupScreen::hostButtonPosition = sf::Vector2f(490, 300);
const sf::Vector2f SetupScreen::buttonTextOffset = sf::Vector2f(20,0);
const sf::Vector2f SetupScreen::vsTextPosition = sf::Vector2f(300, 200);
SetupScreen::SetupScreen(Game& game)
    :Screen(game), name1Text("Player", game.assets.gameScreenAssets.abilityFont, 20), name2Text("Opponent", game.assets.gameScreenAssets.abilityFont, 20)
    ,joinText("Join", game.assets.gameScreenAssets.abilityFont,20), hostText("Host", game.assets.gameScreenAssets.abilityFont, 20)
    ,ipAddr(" ", game.assets.gameScreenAssets.abilityFont, 20), currentSelection(Name1), _currentSocket(0)
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

    // BUTTONS
    std::vector<sf::Sprite> joinButtonSprites;
    for(int i = 0 ; i < 4 ; i++)
    {
        joinButtonSprites.push_back(game.assets.setupScreenAssets.joinButton.createSprite());
    }
    joinButtonSprites[None].setColor(sf::Color(140,70,40));
    joinButtonSprites[Hovered].setColor(sf::Color(200,130,90));
    joinButtonSprites[Disabled].setColor(sf::Color(160,140,130));
    joinButtonSprites[Active].setColor(sf::Color(245,100,25));
    joinButton = zf::SpriteGroup(joinButtonSprites);
    joinButton.setPosition(joinButtonPosition);
    joinText.setPosition(joinButtonPosition+buttonTextOffset);
    joinText.setColor(sf::Color::White);
    std::vector<sf::Sprite> hostButtonSprites;
    for(int i = 0 ; i < 4 ; i++)
    {
        hostButtonSprites.push_back(game.assets.setupScreenAssets.hostButton.createSprite());
    }
    hostButtonSprites[None].setColor(sf::Color(140,70,40));
    hostButtonSprites[Hovered].setColor(sf::Color(200,130,90));
    hostButtonSprites[Disabled].setColor(sf::Color(160,140,130));
    hostButtonSprites[Active].setColor(sf::Color(245,100,25));
    hostButton = zf::SpriteGroup(hostButtonSprites);
    hostButton.setPosition(hostButtonPosition);
    hostText.setPosition(hostButtonPosition+buttonTextOffset);
    hostText.setColor(sf::Color::White);
// IP
    ipAddr.setPosition(ipAddrPosition+nameOffset);
    ipAddr.setColor(sf::Color(0,0,0));
    ipAddrBorder = game.assets.setupScreenAssets.ipAddrBox.createSprite();
    ipAddrBorder.setPosition(ipAddrPosition);
// VS TEXT    
    sf::Text tmp("VS", game.assets.gameScreenAssets.abilityFont, 40);
    tmp.setPosition(vsTextPosition);
    fixedTexts.push_back(tmp);
    tmp = sf::Text("Ip :", game.assets.gameScreenAssets.abilityFont, 20);
    tmp.setPosition(ipAddrPosition - sf::Vector2f(50,0));
    fixedTexts.push_back(tmp);

    name1 = "Player";
    name2 = "Opponent";
    ipAddrString = "";
    setCurrentSelection(Name1);
}

SetupScreen::~SetupScreen()
{
}

void SetupScreen::textInput(char c)
{
    sf::Text& text = currentSelection == Name1 ? name1Text : (currentSelection == Name2 ? name2Text : ipAddr);
    std::string& value = currentSelection == Name1 ? name1 : (currentSelection == Name2 ? name2 : ipAddrString);
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
    else
    {
        ipAddrBorder.setColor(sf::Color::White);
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
    else
    {
        ipAddrBorder.setColor(sf::Color(220,220,100));
    }
}

void SetupScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    window.draw(nameBorder1);
    window.draw(nameBorder2);
    window.draw(name1Text);
    window.draw(name2Text);
    window.draw(ipAddrBorder);
    window.draw(ipAddr);
    for(std::vector<sf::Text>::iterator it = fixedTexts.begin() ; it != fixedTexts.end() ; ++it)
    {
        window.draw(*it); 
    }
    joinButton.draw(window, delta);
    window.draw(joinText);
    hostButton.draw(window, delta);
    window.draw(hostText);
}

void SetupScreen::update(sf::RenderWindow& window, const sf::Time& delta)
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
        else if(ipAddrBorder.getGlobalBounds().contains(mousePosF))
        {
            setCurrentSelection(IpAddr);
        }
        else if(joinButton.bound.contains(mousePosF))
        {
            sf::TcpSocket* socket = new sf::TcpSocket();
            sf::Socket::Status status = socket->connect(ipAddrString, 6999, sf::seconds(5.0));
            if(status == sf::Socket::Done)
            {
                // connected.
            }
            else
            {
                delete socket;
            }
        }
        else if(hostButton.bound.contains(mousePosF))
        {
            
        }
    }
    else
    {
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
