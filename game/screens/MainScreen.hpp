#ifndef _GAME_SCREENS_MAINSCREEN_H_
#define _GAME_SCREENS_MAINSCREEN_H_
#include "Screen.hpp"
#include "../../z_framework/zf_sfml/animations/SimpleAnimator.hpp"
#include "../../z_framework/zf_sfml/SpriteGroup.hpp"
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
class MainScreen : public Screen
{
public:
    static const sf::Vector2f namePosition;
    static const sf::Vector2f nameOffset;
    static const sf::Vector2f joinButtonPosition;
    static const sf::Vector2f hostButtonPosition;
    static const sf::Vector2f localButtonPosition;
    static const sf::Vector2f buttonTextOffset;

    static const sf::Vector2f vsTextPosition;
    static const sf::Vector2f ipAddrPosition;

    static const sf::Vector2f Dialog_Size;
    static const sf::Vector2f Dialog_BG;
    // The other component of the dialogs are offset from the BG.
    static const sf::Vector2f Dialog_NameOffset; // common to both
    static const sf::Vector2f Dialog_NameTextOffset; // common to both
    
    static const sf::Vector2f Dialog_JoinHostButtonOffset;
    static const sf::Vector2f Dialog_JoinHostTextOffset;
    static const sf::Vector2f Dialog_CancelButtonOffset;
    static const sf::Vector2f Dialog_CancelTextOffset;
    
    static const sf::Vector2f Dialog_ButtonTextOffset;

    static const sf::Vector2f Dialog_PortTextBG;
    static const sf::Vector2f Dialog_PortTextOffset;

    static const sf::Vector2f JoinDialog_IpBG;
    static const sf::Vector2f JoinDialog_IpTextOffset;

    static const sf::Vector2f HostDialog_PortLabel;

    MainScreen(Game& game);
    ~MainScreen();
    
    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);
    void textInput(char c);
    void screenEnter();
    void screenExit();
private:
    enum ButtonState
    {
        None = 0,
        Hovered = 1,
        Disabled = 2,
        Active = 3,
    };
    zf::SpriteGroup localButton;
    zf::SpriteGroup hostButton;
    zf::SpriteGroup joinButton;
    sf::Text localText;
    sf::Text hostText; 
    sf::Text joinText;   
    SimpleAnimator _animator;

    // I have to pull this out as a class next time ...
    enum DialogState
    {
        // no dialog will be shown
        NoDialog,
        // Show Join Dialog
        //  1. Name
        //  2. Ip
        //  3. Port
        //  4. Join button 
        //  5. Cancel button
        JoinDialog,
        // Show Host Dialog
        //  1. Name
        //  2. Port
        //  3. Host button
        //  4. Cancel button
        HostDialog,
    };

    enum CurrentTextSelection
    {
        TextSelection_None,
        TextSelection_Name,
        TextSelection_Ip,
        TextSelection_Port
    };
    
    CurrentTextSelection currentTextSelection;
    void setCurrentTextSelection(CurrentTextSelection cs);
    ////// for join dialog ///////
    sf::Sprite joinDialog_ipBg;
    sf::Text joinDialog_ipText;
    ////// specific for host dialog //////
    sf::Text hostDialog_portLabel;
    
    // Common to both dialog.
    sf::Sprite dialog_background;
    sf::Sprite dialog_nameBg;
    sf::Text dialog_nameText;
    // common to both join or host
    zf::SpriteGroup dialog_joinhostButton;
    sf::Text dialog_joinhostText;
    zf::SpriteGroup dialog_cancelButton;
    sf::Text dialog_cancelText;
    sf::Text dialog_portText;
    sf::Sprite dialog_portBg;

    std::string name;
    std::string ip;
    std::string port;

    DialogState currentDialogState;
    float timer;
    void updateButtonState(zf::SpriteGroup& spriteGroup, sf::Vector2f position);

    void setDialogState(DialogState);
    void setupLocalGame();
    void setupHostGame();
    void setupJoinGame();


    void updateText(sf::Text& text, std::string stringValue);
};
#endif
