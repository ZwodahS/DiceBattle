#include "MainScreen.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"
#include <SFML/Network.hpp>
#define DEFAULT_IP_ADDRESS "Ip-address"
#define DEFAULT_PORT "Port"
const sf::Vector2f MainScreen::namePosition = sf::Vector2f(390, 200);
const sf::Vector2f MainScreen::nameOffset = sf::Vector2f(10,0);
const sf::Vector2f MainScreen::ipAddrPosition = sf::Vector2f(150, 300);

const sf::Vector2f MainScreen::localButtonPosition = sf::Vector2f(-33, 200);
const sf::Vector2f MainScreen::hostButtonPosition = sf::Vector2f(-33, 270);
const sf::Vector2f MainScreen::joinButtonPosition = sf::Vector2f(-33, 340);
const sf::Vector2f MainScreen::helpButtonPosition = sf::Vector2f(-33, 410);
const sf::Vector2f MainScreen::buttonTextOffset = sf::Vector2f(20,0);
const sf::Vector2f MainScreen::vsTextPosition = sf::Vector2f(300, 200);

const sf::Vector2f MainScreen::Dialog_Size = sf::Vector2f(300, 200);
const sf::Vector2f MainScreen::Dialog_BG = sf::Vector2f(320 - (MainScreen::Dialog_Size.x / 2), 100);

const sf::Vector2f MainScreen::Dialog_NameOffset = sf::Vector2f(20,20);
const sf::Vector2f MainScreen::Dialog_NameTextOffset = sf::Vector2f(10,0);

const sf::Vector2f MainScreen::Dialog_JoinHostButtonOffset = sf::Vector2f(20,160);
const sf::Vector2f MainScreen::Dialog_CancelButtonOffset = sf::Vector2f(180,160);

const sf::Vector2f MainScreen::Dialog_PortTextBG = sf::Vector2f(200,60);
const sf::Vector2f MainScreen::Dialog_PortTextOffset = sf::Vector2f(10,0);

const sf::Vector2f MainScreen::JoinDialog_IpBG = sf::Vector2f(20,60);
const sf::Vector2f MainScreen::JoinDialog_IpTextOffset = sf::Vector2f(10,0);

const sf::FloatRect MainScreen::Dialog_ButtonSize = sf::FloatRect(0,0,100,30);
MainScreen::MainScreen(Game& game)
    : Screen(game)
    , currentDialogState(NoDialog)
    , joinDialog_ipText(DEFAULT_IP_ADDRESS, game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_nameText("Player name", game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_portText(DEFAULT_PORT, game.assets.gameScreenAssets.abilityFont, 20)
    , name("")
    , ip("")
    , port("")
    , currentTextSelection(TextSelection_None)
    , dialog_joinButton(game.assets.mainScreenAssets.dialog.joinButtonSelected.createSprite(), game.assets.mainScreenAssets.dialog.joinButton.createSprite(), Dialog_ButtonSize)
    , dialog_hostButton(game.assets.mainScreenAssets.dialog.hostButtonSelected.createSprite(), game.assets.mainScreenAssets.dialog.hostButton.createSprite(), Dialog_ButtonSize)
    , dialog_cancelButton(game.assets.mainScreenAssets.dialog.cancelButtonSelected.createSprite(), game.assets.mainScreenAssets.dialog.cancelButton.createSprite(), Dialog_ButtonSize)
    , _joinButton(game.assets.mainScreenAssets.joinButton.createSprite(), sf::Vector2f(30,0), 0.2)
    , _hostButton(game.assets.mainScreenAssets.hostButton.createSprite(), sf::Vector2f(30,0), 0.2)
    , _localButton(game.assets.mainScreenAssets.localButton.createSprite(), sf::Vector2f(30,0), 0.2)
    , _helpButton(game.assets.mainScreenAssets.helpButton.createSprite(), sf::Vector2f(30,0), 0.2)
{
    // BUTTONS
    _joinButton.setPosition(joinButtonPosition + sf::Vector2f(-300,0));
    _hostButton.setPosition(hostButtonPosition + sf::Vector2f(-300,0));
    _localButton.setPosition(localButtonPosition + sf::Vector2f(-300, 0));
    _helpButton.setPosition(helpButtonPosition + sf::Vector2f(-300,0));
    dialog_background = game.assets.mainScreenAssets.dialog.background.createSprite();
    dialog_nameBg = game.assets.mainScreenAssets.dialog.nameBg.createSprite();
    dialog_nameText.setColor(sf::Color(110,110,90));
    // temporary use it for now.
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
    _localButton.draw(window, delta);
    _hostButton.draw(window, delta);
    _joinButton.draw(window, delta);
    _helpButton.draw(window, delta);
    if(currentDialogState == NoDialog)
    {
    }
    else if(currentDialogState == JoinDialog)
    {
        window.draw(dialog_background);
        window.draw(dialog_nameBg);
        window.draw(dialog_nameText);
        dialog_joinButton.draw(window, delta);
        dialog_cancelButton.draw(window, delta);
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
        dialog_hostButton.draw(window,delta);
        dialog_cancelButton.draw(window, delta);
        window.draw(dialog_portBg);
        window.draw(dialog_portText);
    }
}

void MainScreen::update(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput)
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
        if(handleInput)
        {
            zf::Mouse& mouse = _game.mouse;
            sf::Vector2i mousePosi = mouse.getPosition(window);
            sf::Vector2f mousePosf = sf::Vector2f(mousePosi.x, mousePosi.y);
            if(currentDialogState == NoDialog)
            {
                _localButton.updateSelection(mousePosf, delta);
                _hostButton.updateSelection(mousePosf, delta);
                _joinButton.updateSelection(mousePosf, delta);
                _helpButton.updateSelection(mousePosf, delta);

                if(mouse.left.thisReleased)
                {
                    if(_localButton.bound.contains(mousePosf))
                    {
                        setupLocalGame();
                    }
                    else if(_hostButton.bound.contains(mousePosf))
                    {
                        setDialogState(HostDialog);
                    }
                    else if(_joinButton.bound.contains(mousePosf))
                    {
                        setDialogState(JoinDialog);
                    }
                    else if(_helpButton.bound.contains(mousePosf))
                    {
                        _game.toggleShowHelp();
                    }
                }
            }
            else if(currentDialogState == JoinDialog)
            {
                dialog_joinButton.updateSelection(mousePosf);
                dialog_cancelButton.updateSelection(mousePosf);

                if(mouse.left.thisReleased)
                {
                    if(dialog_joinButton.clickBound.contains(mousePosf))
                    {
                        setupJoinGame();
                    }
                    else if(dialog_cancelButton.clickBound.contains(mousePosf))
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
                dialog_hostButton.updateSelection(mousePosf);
                dialog_cancelButton.updateSelection(mousePosf);
                if(mouse.left.thisReleased)
                {
                    if(dialog_hostButton.clickBound.contains(mousePosf))
                    {
                        setupHostGame();
                    }
                    else if(dialog_cancelButton.clickBound.contains(mousePosf))
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
                    // in here we don't really try to change the ip
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
    _animator.moveReferenceTo(_localButton, localButtonPosition, 1.5);
    _animator.moveReferenceTo(_hostButton, hostButtonPosition, 1.5);
    _animator.moveReferenceTo(_joinButton, joinButtonPosition, 1.5);
    _animator.moveReferenceTo(_helpButton, helpButtonPosition, 1.5);
    timer = 2;
}

void MainScreen::screenExit()
{
    _animator.moveReference(_localButton, sf::Vector2f(-700,0), 1.5);
    _animator.moveReference(_hostButton, sf::Vector2f(-700,0), 1.5);
    _animator.moveReference(_joinButton, sf::Vector2f(-700,0), 1.5);
    _animator.moveReference(_helpButton, sf::Vector2f(-700,0), 1.5);
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
    currentDialogState = state;
    if(currentDialogState == JoinDialog)
    {
        dialog_background.setPosition(Dialog_BG);
        dialog_nameBg.setPosition(Dialog_BG + Dialog_NameOffset);
        dialog_nameText.setPosition(Dialog_BG + Dialog_NameOffset + Dialog_NameTextOffset);
        dialog_joinButton.setPosition(Dialog_BG + Dialog_JoinHostButtonOffset);
        dialog_cancelButton.setPosition(Dialog_BG + Dialog_CancelButtonOffset);
        dialog_portBg.setPosition(Dialog_BG + Dialog_PortTextBG);
        dialog_portText.setPosition(Dialog_BG + Dialog_PortTextBG + Dialog_PortTextOffset);
        joinDialog_ipBg.setPosition(Dialog_BG + JoinDialog_IpBG);
        joinDialog_ipText.setPosition(Dialog_BG + JoinDialog_IpBG + JoinDialog_IpTextOffset);
        ip = " ";
        port = " ";
    }
    else if(currentDialogState == HostDialog)
    {
        /**
         * Commented out because the ipaddress doesn't seems to be accurate.
         * In the case that this is to be implemented, remember to draw it.
         * I know it is bad to leave commented code. But this is functional !
        sf::IpAddress ip = sf::IpAddress::getPublicAddress(sf::seconds(3));
        if(ip == sf::IpAddress::None)
        {
            ip = sf::IpAddress::getLocalAddress();
        }
        joinDialog_ipBg.setPosition(Dialog_BG + JoinDialog_IpBG);
        joinDialog_ipText.setPosition(Dialog_BG + JoinDialog_IpBG + JoinDialog_IpTextOffset);
        joinDialog_ipText.setString(ip.toString());
        */
        dialog_background.setPosition(Dialog_BG);
        dialog_nameBg.setPosition(Dialog_BG + Dialog_NameOffset);
        dialog_nameText.setPosition(Dialog_BG + Dialog_NameOffset + Dialog_NameTextOffset);
        dialog_hostButton.setPosition(Dialog_BG + Dialog_JoinHostButtonOffset);
        dialog_cancelButton.setPosition(Dialog_BG + Dialog_CancelButtonOffset);
        dialog_portBg.setPosition(Dialog_BG + Dialog_PortTextBG);
        dialog_portText.setPosition(Dialog_BG + Dialog_PortTextBG + Dialog_PortTextOffset);
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
