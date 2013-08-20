#include "MainScreen.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"
#define DEFAULT_IP_ADDRESS "Ip-address"
#define DEFAULT_PORT "Port"
const sf::Vector2f MainScreen::namePosition = sf::Vector2f(390, 200);
const sf::Vector2f MainScreen::nameOffset = sf::Vector2f(10,0);
const sf::Vector2f MainScreen::ipAddrPosition = sf::Vector2f(150, 300);
const sf::Vector2f MainScreen::localButtonPosition = sf::Vector2f(100, 300);
const sf::Vector2f MainScreen::joinButtonPosition = sf::Vector2f(250, 300);
const sf::Vector2f MainScreen::hostButtonPosition = sf::Vector2f(400, 300);
const sf::Vector2f MainScreen::buttonTextOffset = sf::Vector2f(20,0);
const sf::Vector2f MainScreen::vsTextPosition = sf::Vector2f(300, 200);

const sf::Vector2f MainScreen::Dialog_Size = sf::Vector2f(300, 200);
const sf::Vector2f MainScreen::Dialog_BG = sf::Vector2f(320 - (MainScreen::Dialog_Size.x / 2), 100);

const sf::Vector2f MainScreen::Dialog_NameOffset = sf::Vector2f(20,20);
const sf::Vector2f MainScreen::Dialog_NameTextOffset = sf::Vector2f(10,0);

const sf::Vector2f MainScreen::Dialog_JoinHostButtonOffset = sf::Vector2f(20,160);
const sf::Vector2f MainScreen::Dialog_JoinHostTextOffset = sf::Vector2f(20,0);
const sf::Vector2f MainScreen::Dialog_CancelButtonOffset = sf::Vector2f(180,160);
const sf::Vector2f MainScreen::Dialog_CancelTextOffset = sf::Vector2f(15,0);


const sf::Vector2f MainScreen::Dialog_PortTextBG = sf::Vector2f(200,60);
const sf::Vector2f MainScreen::Dialog_PortTextOffset = sf::Vector2f(10,0);

const sf::Vector2f MainScreen::JoinDialog_IpBG = sf::Vector2f(20,60);
const sf::Vector2f MainScreen::JoinDialog_IpTextOffset = sf::Vector2f(10,0);

const sf::Vector2f MainScreen::HostDialog_PortLabel = sf::Vector2f(0,0);
MainScreen::MainScreen(Game& game)
    : Screen(game)
    , joinText("Join", game.assets.gameScreenAssets.abilityFont,20)
    , hostText("Host", game.assets.gameScreenAssets.abilityFont, 20)
    , localText("Local", game.assets.gameScreenAssets.abilityFont, 20)
    , currentDialogState(NoDialog)
    , joinDialog_ipText(DEFAULT_IP_ADDRESS, game.assets.gameScreenAssets.abilityFont, 20)
    , hostDialog_portLabel("Port :", game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_nameText("Player name", game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_joinhostText("Join", game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_cancelText("Cancel", game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_portText(DEFAULT_PORT, game.assets.gameScreenAssets.abilityFont, 20)
    , name("")
    , ip("")
    , port("")
    , currentTextSelection(TextSelection_None)
{
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
    joinButton.setPosition(joinButtonPosition + sf::Vector2f(0,700));
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
    hostButton.setPosition(hostButtonPosition + sf::Vector2f(700,0));
    hostText.setPosition(hostButtonPosition+buttonTextOffset);
    hostText.setColor(sf::Color::White);

    std::vector<sf::Sprite> localButtonSprites;
    for(int i = 0 ; i < 4 ; i++)
    {
        localButtonSprites.push_back(game.assets.setupScreenAssets.hostButton.createSprite());
    }
    localButtonSprites[None].setColor(sf::Color(140,70,40));
    localButtonSprites[Hovered].setColor(sf::Color(200,130,90));
    localButtonSprites[Disabled].setColor(sf::Color(160,140,130));
    localButtonSprites[Active].setColor(sf::Color(245,100,25));
    localButton = zf::SpriteGroup(localButtonSprites);
    localButton.setPosition(localButtonPosition + sf::Vector2f(-700, 0));
    localText.setPosition(localButtonPosition+buttonTextOffset);
    localText.setColor(sf::Color::White);

    dialog_background = game.assets.mainScreenAssets.dialog.background.createSprite();
    dialog_nameBg = game.assets.mainScreenAssets.dialog.nameBg.createSprite();
    dialog_nameText.setColor(sf::Color(110,110,90));
    // temporary use it for now.
    dialog_joinhostButton = zf::SpriteGroup(hostButtonSprites);
    dialog_cancelButton = zf::SpriteGroup(hostButtonSprites);
    dialog_portBg = game.assets.mainScreenAssets.dialog.portBg.createSprite();
    dialog_portText.setColor(sf::Color(110,110,90));
    joinDialog_ipBg = game.assets.mainScreenAssets.dialog.ipBg.createSprite();
    joinDialog_ipText.setColor(sf::Color(110,110,90));
    
}

MainScreen::~MainScreen()
{
}

void MainScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    localButton.draw(window, delta);
    hostButton.draw(window, delta);
    joinButton.draw(window, delta);
    window.draw(localText);
    window.draw(hostText);
    window.draw(joinText);
    if(currentDialogState == NoDialog)
    {
    }
    else if(currentDialogState == JoinDialog)
    {
        window.draw(dialog_background);
        window.draw(dialog_nameBg);
        window.draw(dialog_nameText);
        dialog_joinhostButton.draw(window, delta);
        window.draw(dialog_joinhostText);
        dialog_cancelButton.draw(window, delta);
        window.draw(dialog_cancelText);
        window.draw(dialog_portBg);
        window.draw(dialog_portText);
        window.draw(joinDialog_ipBg);
        window.draw(joinDialog_ipText);
    }
    else if(currentDialogState == HostDialog)
    {
        window.draw(dialog_background);
        window.draw(dialog_nameBg);
        window.draw(dialog_nameText);
        dialog_joinhostButton.draw(window, delta);
        window.draw(dialog_joinhostText);
        dialog_cancelButton.draw(window, delta);
        window.draw(dialog_cancelText);
        window.draw(dialog_portBg);
        window.draw(dialog_portText);
        window.draw(hostDialog_portLabel);
    }
}

void MainScreen::update(sf::RenderWindow& window, const sf::Time& delta)
{
    _animator.update(window, delta);
    if(screenState == Screen::Entering)
    {
        timer -= delta.asSeconds();
        if(timer <= 0)
        {
            screenState = Screen::Active;
        }
    }
    else if(screenState == Screen::Active)
    {
        if(_game.isFocused)
        {
            zf::Mouse& mouse = _game.mouse;
            sf::Vector2i mousePosi = mouse.getPosition(window);
            sf::Vector2f mousePosf = sf::Vector2f(mousePosi.x, mousePosi.y);
            if(currentDialogState == NoDialog)
            {
                updateButtonState(localButton, mousePosf);
                updateButtonState(hostButton, mousePosf);
                updateButtonState(joinButton, mousePosf);

                if(mouse.left.thisReleased)
                {
                    if(localButton.bound.contains(mousePosf))
                    {
                        setupLocalGame();
                    }
                    else if(hostButton.bound.contains(mousePosf))
                    {
                        setDialogState(HostDialog);
                    }
                    else if(joinButton.bound.contains(mousePosf))
                    {
                        setDialogState(JoinDialog);
                    }
                }
            }
            else if(currentDialogState == JoinDialog)
            {
                updateButtonState(dialog_joinhostButton, mousePosf);
                updateButtonState(dialog_cancelButton, mousePosf);

                if(mouse.left.thisReleased)
                {
                    if(dialog_joinhostButton.bound.contains(mousePosf))
                    {
                        setupJoinGame();
                    }
                    else if(dialog_cancelButton.bound.contains(mousePosf))
                    {
                        setDialogState(NoDialog);
                    }
                    else if(dialog_nameBg.getGlobalBounds().contains(mousePosf))
                    {
                        setCurrentTextSelection(TextSelection_Name);
                    }
                    else if(dialog_portBg.getGlobalBounds().contains(mousePosf))
                    {
                        setCurrentTextSelection(TextSelection_Port);
                    }
                    else if(joinDialog_ipBg.getGlobalBounds().contains(mousePosf))
                    {
                        setCurrentTextSelection(TextSelection_Ip);
                    }
                }
            }
            else if(currentDialogState == HostDialog)
            {
                updateButtonState(dialog_joinhostButton, mousePosf);
                updateButtonState(dialog_cancelButton, mousePosf);
                if(mouse.left.thisReleased)
                {
                    if(dialog_joinhostButton.bound.contains(mousePosf))
                    {
                        setupHostGame();
                    }
                    else if(dialog_cancelButton.bound.contains(mousePosf))
                    {
                        setDialogState(NoDialog);
                    }
                    else if(dialog_nameBg.getGlobalBounds().contains(mousePosf))
                    {
                        setCurrentTextSelection(TextSelection_Name);
                    }
                    else if(dialog_portBg.getGlobalBounds().contains(mousePosf))
                    {
                        setCurrentTextSelection(TextSelection_Port);
                    }
                }
            }
        }
    }
    else if(screenState == Screen::Exiting)
    {
        timer -= delta.asSeconds();
        if(timer <= 0)
        {
            screenState = Screen::Exited;
        }
    }
}

void MainScreen::textInput(char c)
{
    if(screenState == Screen::Active)
    {
        if(currentTextSelection == TextSelection_None)
        {
        }
        else
        {
            sf::Text& text = currentTextSelection == TextSelection_Name ? dialog_nameText : currentTextSelection == TextSelection_Ip ? joinDialog_ipText : dialog_portText;
            std::string& value = currentTextSelection == TextSelection_Name ? name : currentTextSelection == TextSelection_Ip ? ip : port;
            int maxSize = currentTextSelection == TextSelection_Name ? 15 : currentTextSelection == TextSelection_Ip ? 16 : 5;
            if(c >= 32 && c < 127)
            {
                if(value == " ")
                {
                    value = c;
                }
                else if(value.size() < maxSize)
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
    }
}

void MainScreen::screenEnter()
{
    screenState = Screen::Entering;
    _animator.moveReferenceTo(localButton, localButtonPosition, 1.5);
    _animator.moveReferenceTo(hostButton, hostButtonPosition, 1.5);
    _animator.moveReferenceTo(joinButton, joinButtonPosition, 1.5);
    timer = 2;
}

void MainScreen::screenExit()
{
    _animator.moveReferenceTo(localButton, localButtonPosition + sf::Vector2f(-700,0), 1.5);
    _animator.moveReferenceTo(hostButton, hostButtonPosition + sf::Vector2f(700,0), 1.5);
    _animator.moveReferenceTo(joinButton, joinButtonPosition + sf::Vector2f(0,700), 1.5);
    screenState = Screen::Exiting;
    timer = 1;
}

void MainScreen::updateButtonState(zf::SpriteGroup& spriteGroup, sf::Vector2f position)
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

void MainScreen::setDialogState(DialogState state)
{
    localButton.setState(None);
    joinButton.setState(None);
    hostButton.setState(None);
    currentDialogState = state;
    if(currentDialogState == JoinDialog)
    {
        dialog_background.setPosition(Dialog_BG);
        dialog_nameBg.setPosition(Dialog_BG + Dialog_NameOffset);
        dialog_nameText.setPosition(Dialog_BG + Dialog_NameOffset + Dialog_NameTextOffset);
        dialog_joinhostButton.setPosition(Dialog_BG + Dialog_JoinHostButtonOffset);
        dialog_joinhostText.setPosition(Dialog_BG + Dialog_JoinHostButtonOffset + Dialog_JoinHostTextOffset);
        dialog_joinhostText.setString("Join");
        dialog_cancelButton.setPosition(Dialog_BG + Dialog_CancelButtonOffset);
        dialog_cancelText.setPosition(Dialog_BG + Dialog_CancelButtonOffset + Dialog_CancelTextOffset);
        dialog_portBg.setPosition(Dialog_BG + Dialog_PortTextBG);
        dialog_portText.setPosition(Dialog_BG + Dialog_PortTextBG + Dialog_PortTextOffset);
        joinDialog_ipBg.setPosition(Dialog_BG + JoinDialog_IpBG);
        joinDialog_ipText.setPosition(Dialog_BG + JoinDialog_IpBG + JoinDialog_IpTextOffset);
        ip = " ";
        port = " ";
    }
    else if(currentDialogState == HostDialog)
    {
        dialog_background.setPosition(Dialog_BG);
        dialog_nameBg.setPosition(Dialog_BG + Dialog_NameOffset);
        dialog_nameText.setPosition(Dialog_BG + Dialog_NameOffset + Dialog_NameTextOffset);
        dialog_joinhostButton.setPosition(Dialog_BG + Dialog_JoinHostButtonOffset);
        dialog_joinhostText.setPosition(Dialog_BG + Dialog_JoinHostButtonOffset + Dialog_JoinHostTextOffset);
        dialog_joinhostText.setString("Host");
        dialog_cancelButton.setPosition(Dialog_BG + Dialog_CancelButtonOffset);
        dialog_cancelText.setPosition(Dialog_BG + Dialog_CancelButtonOffset + Dialog_CancelTextOffset);
        dialog_portBg.setPosition(Dialog_BG + Dialog_PortTextBG);
        dialog_portText.setPosition(Dialog_BG + Dialog_PortTextBG + Dialog_PortTextOffset);
        hostDialog_portLabel.setPosition(Dialog_BG + Dialog_PortTextBG - sf::Vector2f(100,0));
        ip = " ";
        port = " ";
    }
}

void MainScreen::setupLocalGame()
{
    _game.setupLocalGame();
}

void MainScreen::setupHostGame()
{
    if(name == "")
    {
        setCurrentTextSelection(TextSelection_Name);
        updateText(dialog_nameText, name);
        return;
    }
    unsigned short value;
    bool success = zf::toUShort(port,value);
    if(success)
    {
        _game.setupHosting(value, name);
    }
}

void MainScreen::setupJoinGame()
{
    if(name == "")
    {
        setCurrentTextSelection(TextSelection_Name);
        updateText(dialog_nameText, name);
        return;
    }
    unsigned short value;
    bool success = zf::toUShort(port, value);
    if(success)
    {
        _game.setupJoin(name, ip, value);
    }
}


void MainScreen::updateText(sf::Text& text, std::string stringValue)
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
void MainScreen::setCurrentTextSelection(CurrentTextSelection cs)
{
    sf::Sprite& oldBg = currentTextSelection == TextSelection_Name ? dialog_nameBg : currentTextSelection == TextSelection_Ip ? joinDialog_ipBg : dialog_portBg;
    oldBg.setColor(sf::Color::White);
    currentTextSelection = cs;
    sf::Sprite& newBg = currentTextSelection == TextSelection_Name ? dialog_nameBg : currentTextSelection == TextSelection_Ip ? joinDialog_ipBg : dialog_portBg;
    newBg.setColor(sf::Color(220,220,100));
}

void MainScreen::waitingForReply()
{
    _waitingForReply = true;
}

void MainScreen::replyTimeout()
{
    _waitingForReply = false;
}
