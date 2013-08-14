#include "MainScreen.hpp"
#include "../Game.hpp"
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


const sf::Vector2f MainScreen::Dialog_PortTextBG = sf::Vector2f(1000,1000);
const sf::Vector2f MainScreen::Dialog_PortTextOffset = sf::Vector2f(0,0);

const sf::Vector2f MainScreen::JoinDialog_IpBG = sf::Vector2f(20,60);
const sf::Vector2f MainScreen::JoinDialog_IpTextOffset = sf::Vector2f(10,0);

const sf::Vector2f MainScreen::HostDialog_PortLabel = sf::Vector2f(0,0);
MainScreen::MainScreen(Game& game)
    : Screen(game)
    , joinText("Join", game.assets.gameScreenAssets.abilityFont,20)
    , hostText("Host", game.assets.gameScreenAssets.abilityFont, 20)
    , localText("Local", game.assets.gameScreenAssets.abilityFont, 20)
    , currentDialogState(NoDialog)
    , joinDialog_ipText("Ip address", game.assets.gameScreenAssets.abilityFont, 20)
    , hostDialog_portLabel("Host Port", game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_nameText("Player name", game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_joinhostText("Join", game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_cancelText("Cancel", game.assets.gameScreenAssets.abilityFont, 20)
    , dialog_portText("Port?", game.assets.gameScreenAssets.abilityFont, 20)
    , name("Player")
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
    localButton.setPosition(localButtonPosition + sf::Vector2f(0, -700));
    localText.setPosition(localButtonPosition+buttonTextOffset);
    localText.setColor(sf::Color::White);

    dialog_background = game.assets.mainScreenAssets.dialog.background.createSprite();
    dialog_nameBg = game.assets.mainScreenAssets.dialog.nameBg.createSprite();
    dialog_nameText.setColor(sf::Color(110,110,90));
    // temporary use it for now.
    dialog_joinhostButton = zf::SpriteGroup(hostButtonSprites);
    dialog_cancelButton = zf::SpriteGroup(hostButtonSprites);
    dialog_portBg = game.assets.mainScreenAssets.dialog.portBg.createSprite();

    joinDialog_ipBg = game.assets.mainScreenAssets.dialog.ipBg.createSprite();
    joinDialog_ipText.setColor(sf::Color(110,110,90));
    
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
                        // process join 
                    }
                    else if(dialog_cancelButton.bound.contains(mousePosf))
                    {
                        setDialogState(NoDialog);
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
                        // process host 
                    }
                    else if(dialog_cancelButton.bound.contains(mousePosf))
                    {
                        setDialogState(NoDialog);
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
    screenState = Screen::Exiting;
    timer = 2;
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
    }
}
