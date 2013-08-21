#include "SetupScreen.hpp"
#include "../Game.hpp"
const sf::Vector2f SetupScreen::name1Position = sf::Vector2f(50, 200);
const sf::Vector2f SetupScreen::name2Position = sf::Vector2f(390, 200);
const sf::Vector2f SetupScreen::nameOffset = sf::Vector2f(10,0);
const sf::Vector2f SetupScreen::startButtonPosition = sf::Vector2f(270, 400);
const sf::Vector2f SetupScreen::buttonTextOffset = sf::Vector2f(20,0);
const sf::Vector2f SetupScreen::vsTextPosition = sf::Vector2f(300, 200);
SetupScreen::SetupScreen(Game& game, SetupType st, zf::GameSetup* setup)
    :Screen(game), setupType(st), name1Text("Player1", game.assets.gameScreenAssets.abilityFont, 20), name2Text("Player2", game.assets.gameScreenAssets.abilityFont, 20)
    , currentSelection(Name1), startText("Start", game.assets.gameScreenAssets.abilityFont, 20), _gameSetup(setup)
{
    if(st == Local)
    {
        player1.uniqueId = "Player1";
        player1.name = "Player1";
        player2.uniqueId = "Player2";
        player2.name = "Player2";
    }
    else if(st == Host)
    {
        if(_gameSetup != 0)
        {
            _gameSetup->addGameSetupListener(*this);
        }
        name1Text.setString(" ");
        name2Text.setString(" ");
        player1.uniqueId = "";
        player1.name = "";
        player1.role = "1";
        player2.uniqueId = "";
        player2.name = "";
        player2.role = "2";
    }    
    else 
    {
        if(_gameSetup != 0)
        {
            _gameSetup->addGameSetupListener(*this);
        }
        name1Text.setString(" ");
        name2Text.setString(" ");
    }
    // name and the name box
    //
    std::vector<sf::Sprite> nameBoxSprites;
    for(int i = 0 ; i < 4 ; i++)
    {
        nameBoxSprites.push_back(game.assets.setupScreenAssets.nameBox.createSprite());
    }
    nameBoxSprites[None].setColor(sf::Color(255,255,255,255));
    nameBoxSprites[Hovered].setColor(sf::Color(220,220,110,255));
    nameBoxSprites[Disabled].setColor(sf::Color(200,200,165,255));
    nameBoxSprites[Active].setColor(sf::Color(255,255,50,255));
    nameBorder1 = zf::SpriteGroup(nameBoxSprites);
    nameBorder1.setPosition(name1Position);
    name1Text.setPosition(name1Position + nameOffset);
    name1Text.setColor(sf::Color(0,0,0));
    nameBorder2 = zf::SpriteGroup(nameBoxSprites);
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

    setCurrentSelection(Name1);
}

SetupScreen::~SetupScreen()
{
    if(_gameSetup != 0)
    {
        _gameSetup->removeGameSetupListener(*this);
    }
}

void SetupScreen::textInput(char c)
{
    // if not local, there is no need for text input
    if(setupType != Local)
    {
        return;
    }
    sf::Text& text = currentSelection == Name1 ? name1Text : name2Text;
    std::string& value = currentSelection == Name1 ? player1.name : player2.name;
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
        nameBorder1.setState(None);
    }
    else if(currentSelection == Name2)
    {
        nameBorder2.setState(None);
    }
    currentSelection = cs;
    if(currentSelection == Name1)
    {
        nameBorder1.setState(Active);
    }
    else if(currentSelection == Name2)
    {
        nameBorder2.setState(Active);
    }
}

void SetupScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    nameBorder1.draw(window, delta);
    nameBorder2.draw(window, delta);
    window.draw(name1Text);
    window.draw(name2Text);
    for(std::vector<sf::Text>::iterator it = fixedTexts.begin() ; it != fixedTexts.end() ; ++it)
    {
        window.draw(*it); 
    }
    if(setupType == Local || setupType == Host)
    {
        startButton.draw(window, delta);
    }
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
            if(setupType == Local)
            {
                if(nameBorder1.bound.contains(mousePosF))
                {
                    setCurrentSelection(Name1);
                }
                else if(nameBorder2.bound.contains(mousePosF))
                {
                    setCurrentSelection(Name2);
                }
                else if(startButton.bound.contains(mousePosF))
                {
                    _game.startLocalGame(player1.name, player2.name);                
                }
            }
            else
            {
                if(nameBorder1.bound.contains(mousePosF))
                {
                    if(player1.uniqueId == "")
                    {
                        _gameSetup->setRole("1");
                    }
                }
                else if(nameBorder2.bound.contains(mousePosF))
                {
                    if(player2.uniqueId == "")
                    {
                        _gameSetup->setRole("2");
                    }
                }
                else if(startButton.bound.contains(mousePosF))
                {
                    // make sure we are host
                    if(setupType == Host)
                    {
                        std::string r = _gameSetup->getLocalRole();
                        PlayerRole::ePlayerRole role;
                        if(r == "1")
                        {
                            role = PlayerRole::PlayerOne;
                        }
                        else if(r == "2")
                        {
                            role = PlayerRole::PlayerTwo;
                        }
                        else
                        {
                            role = PlayerRole::Observer;
                        }
                        _game.startNetworkGame(_gameSetup, role);
                    }
                }
            }
        }
        else
        {
            updateButtonState(startButton, mousePosF);
            // if it is not local, then the text field is not allow to be edited.
            // It will become a button
            if(setupType != Local) 
            {
                updateButtonState(nameBorder1, mousePosF);
                updateButtonState(nameBorder2, mousePosF);        
            }
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
    if(spriteGroup.state == Active) // if already active, do nothing
    {
    }
    else if(spriteGroup.bound.contains(position))
    {
        spriteGroup.setState(Hovered); 
    }
    else
    {
        spriteGroup.setState(None);
    }
}

void SetupScreen::gameStarts()
{
    // only start the game if we are the client
    if(setupType == Remote)
    {
        std::string r = _gameSetup->getLocalRole();
        PlayerRole::ePlayerRole role = r == "1" ? PlayerRole::PlayerOne : r == "2" ? PlayerRole::PlayerTwo : PlayerRole::Observer;
        _game.joinNetworkGame(_gameSetup, role);
    }
}
void SetupScreen::joinSuccess(std::string name, std::string role)
{
}
void SetupScreen::playerJoined(std::string uniqueId, std::string name, std::string role)
{
    PlayerObj player;
    player.uniqueId = uniqueId;
    player.name = name;
    player.role = role;
    updatePlayer(player);
    if(_gameSetup->isHosting() && player2.uniqueId == "")
    {
        // force the new player role to be 2
        _gameSetup->assignRole(uniqueId, "2");
    }
}
void SetupScreen::playerSwitchRole(std::string uniqueId, std::string name, std::string oldRole, std::string newRole)
{
    PlayerObj player;
    player.uniqueId = uniqueId;
    player.name = name;
    player.role = oldRole;
    removePlayer(player);
    player.role = newRole;
    updatePlayer(player);
}
void SetupScreen::playerLeft(std::string uniqueId, std::string name, std::string role)
{
}

void SetupScreen::removePlayer(PlayerObj player)
{
    if(player.role == "1")
    {
        player1.uniqueId = "";
        player1.name = "";
        updateText(name1Text, player1.name);
    }
    else if(player.role == "2")
    {
        player2.uniqueId = "";
        player2.name = "";
        updateText(name2Text, player2.name);
    }
    else
    {
        for(std::vector<PlayerObj>::iterator it = observers.begin() ; it != observers.end() ; )
        {    
            if((*it).uniqueId == player.uniqueId)
            {
                it = observers.erase(it);
                continue;
            }
            ++it;
        }
    }
}

void SetupScreen::updatePlayer(PlayerObj player)
{
    if(player.role == "1")
    {
        player1 = player;
        updateText(name1Text, player1.name);
    }
    else if(player.role == "2")
    {
        player2 = player;
        updateText(name2Text, player2.name);
    }
    else
    {
        for(std::vector<PlayerObj>::iterator it = observers.begin() ; it != observers.end() ; )
        {    
        }
    }
}
