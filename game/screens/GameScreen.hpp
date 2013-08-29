#ifndef _GAME_SCREENS_GAMESCREEN_H_
#define _GAME_SCREENS_GAMESCREEN_H_
#include "Screen.hpp"
#include "../constants.hpp"
#include "../messages/g_messages.hpp"
#include "../../z_framework/zf_sfml/animations/SimpleAnimator.hpp"
#include "../../z_framework/zf_sfml/Button.hpp"
#include "GameScreenViewer.hpp"
#include "../logic/GeneralUpdater.hpp"
#include <vector>
#include <queue>
class GameViewer;
class GameUpdater;
class Game;
class Battle;
class Ability;
class GameScreen : public Screen 
{
public:
    static const int AbilityDisplayed;
    static const int Ability_X;
    static const int Ability_Y[7];
    static const int AbilityOffScreen_Y[7];
    static const int DieX;
    static const int DieY[7];
    static const int UnitPositionX[2];
    static const int UnitPositionY[2];
    static const sf::FloatRect RollButtonSize;
    static const sf::FloatRect DoneButtonSize;
    static const sf::FloatRect BackToSetupButtonSize;
    static const sf::Vector2f RollButtonPosition;
    static const sf::Vector2f DoneButtonPosition;
    static const sf::Vector2f RulesButtonPosition;
    static const sf::Vector2f BackToSetupButtonPosition;
    static const sf::Vector2f ResultDialogPosition;
    static const sf::Vector2f ResultTextPosition;
    static const float FadeSpeed;
    static const sf::Vector2f AbilityMoveSpeed;
    enum GameScreenState // kind of mimic the state in Battle object but include all the intermediate animation state
    {
        Empty, // The initial state of the screen.
        AnimatingIn, // When Game Start has been call, and all the object starts to animate in.
        GameReady, // When all the objects has animated in, the game is ready but before active turn is called.
        DiceIn, // Dice is animating in
        DiceNotRolled, // When active turn is set, dice is not rolled.
        DiceRolling, // animating the randomness
        DiceRolled, // When a dice has been used.
        AnimatingAbilityUsed, // animates the ability being used.
        AbilityUsed, // When an ability has been used.
        AnimatingTurnEnds, // AnimatesTurnEnd
        GameEnding,
        GameEnd,
    }; 

    static const float RandomizerChangeRate = 0.1;
    static const sf::Int32 DiceSize = 48;
    GameScreen(Game& game, Battle& battle, PlayerRole::ePlayerRole role, GameType::eGameType gameType);
    ~GameScreen();

    void screenEnter();
    void screenExit();

    void textInput(char c);
    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_empty(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_animatingIn(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_gameReady(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_diceIn(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_diceNotRolled(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_diceRolling(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_diceRolled(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_animatingAbilityUsed(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_abilityUsed(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_animatingTurnEnds(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_gameEnding(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void update_gameEnd(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);

    void update_setDice(std::vector<Die>& dice);
    void removeMessageUntilType(Message::MessageType type);    

    void update_processMessage(DB_ActiveTurnMessage* message);
    void update_processMessage(DB_DiceRolledResultMessage* message);
    void update_processMessage(DB_EndGameMessage* message);
    void update_processMessage(DB_EndTurnMessage* message);
    void update_processMessage(DB_NewDiceMessage* message);
    std::queue<Message*> messages;
    void freeFirstMessage();
    /**
     * Used by GameScreenViewer
     */
    void sendMessage(DB_GameStartMessage& message);
    void sendMessage(DB_ActiveTurnMessage& message);
    void sendMessage(DB_AskForActionMessage& message);
    void sendMessage(DB_AbilityUsedMessage& message);
    void sendMessage(DB_DiceRolledResultMessage& message);
    void sendMessage(DB_NewDiceMessage& message);
    void sendMessage(DB_EndTurnMessage& message);
    void sendMessage(DB_EndGameMessage& message);

    // clean up
    void freeBattle();
private:
    /// store the game type ///
    GameType::eGameType _gameType;

    ///// all the sprites of the game /////
    //////// DIE SPRITE /////////
    class DieSprite : public iAnimatable
    {
        static const sf::Vector2f LockOffset;
    public:
        DieSprite(Die die, std::vector<sf::Sprite> faces, sf::Sprite dieBorder, sf::Sprite selectionBorder, sf::Sprite lockIcon);
        Die die;
        std::vector<sf::Sprite> faces;
        sf::Sprite dieBorder;
        sf::Sprite selectionBorder;
        sf::Sprite lockIcon;
        sf::Int32 currentFaceId;
        float randomizerTimer;
        sf::FloatRect clickBound;
        bool random;
        bool visible;
        bool selected;
        bool locked;
        void setDie(Die& die);
        void toggleLocked();
        void toggleSelection();
        void setSelected(bool selected);
        void setEmpty(bool e);
        void setRandom(bool r);
        void setVisible(bool v);
        void update(sf::RenderWindow& window, const sf::Time& delta);
        void draw(sf::RenderWindow& window, const sf::Time& delta);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        void move(sf::Vector2f move);
        void setAlpha(float alpha);
        void setColor(sf::Color color);
    };
    DieSprite makeDie(Die& d);
    ///////// END OF DIESPRITE ////////
    //////// Unit Sprite //////
    class UnitSprite : public iAnimatable
    {
    public:
        UnitSprite(Unit& unit, sf::Sprite bg, sf::Sprite heart, sf::Sprite armor, sf::Sprite stunned, sf::Sprite burnt, sf::Sprite frozen, sf::Text name, sf::Text currentHp, sf::Text shieldCounter, sf::Text genericCounter);
        Unit* unit;
        sf::Sprite background;
        sf::Sprite heartSprite;
        sf::Sprite armorSprite;
        sf::Sprite stunnedSprite;
        sf::Sprite burntSprite;
        sf::Sprite frozenSprite;
        sf::Text nameText;
        sf::Text currentHpText;
        sf::Text shieldText;
        sf::Text stunnedText;
        sf::Text burntText;
        sf::Text frozenText;
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        void updateData();
        void draw(sf::RenderWindow& window, const sf::Time& delta);
        void update(sf::RenderWindow& window, const sf::Time& delta);
        void resetUnitStats();
        void setActive(bool active);
        void setAlpha(float alpha);
        void setColor(sf::Color color);
        void move(sf::Vector2f move);
        sf::FloatRect clickBound;
    }; 
    UnitSprite makeUnitSprite(Unit& unit);
    //////// End of Unit Sprite /////
    /////// Ability Sprite //////
    class AbilitySprite : iAnimatable
    {
    public:
        AbilitySprite(const Ability& ability, std::vector<sf::Sprite> cost, std::vector<sf::Sprite> effectsSymbol, std::vector<sf::Text> effectsText, sf::Sprite background, sf::Text nameText);
        Ability ability;
        std::vector<sf::Sprite> cost; 
        std::vector<sf::Sprite> effectsSymbol;
        std::vector<sf::Text> effectsText;
        sf::Text nameText;
        sf::Sprite background;
        sf::FloatRect clickBound;
        sf::Vector2f finalPosition;
        bool fade;
        float alpha;
        sf::Vector2f moveSpeed;
        /**
         * Set the position of this ability sprite. It defines the top left corner of the sprite.
         */
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        void draw(sf::RenderWindow& window, const sf::Time& delta);
        void update(sf::RenderWindow& window, const sf::Time& delta);
        void setAlpha(float alpha);
        void setColor(sf::Color color);
        void move(sf::Vector2f move);
    };
    AbilitySprite makeAbilitySprite(const Ability& ability);
    /////// End of Ability Sprite //////

    ////////// Ability Sprites Stuffs ////////
    /**
     * List of ability sprites.
     */
    std::vector<AbilitySprite> _abilitySprites;
    /**
     * Check if the screen has AbilitySprite for this ability.
     */
    bool hasAbilitySprite(Ability a);
    /**
     * Get and remove an ability sprite for this ability. If the ability do not exist, then create a new AbilitySprite for this ability.
     */
    AbilitySprite getAndRemoveAbilitySprite(Ability a);
    /**
     * Set a new set of abilities. This will also animates the ability sprites.
     */
    void setMatchedAbilities(std::vector<Ability> abilities);
    /**
     * Animate an ability used.
     */
    void animate_abilityUsed(Ability& ability);
    ////////// End of Ability Sprites Stuffs ///////
    
    ////////// Dice Sprites Stuffs ///////////    
    /**
     * The list of dice sprites that is current in the screen
     */
    std::vector<DieSprite> _diceSprites;
    /**
     * The list of dice sprites that is leaving the screen.
     */
    std::vector<DieSprite> _leavingDiceSprites;
    /**
     * Set a die
     */
    void setDie(Die& die);
    /**
     * Set a list of dice
     */
    void setDice(std::vector<Die>& dice);
    /**
     * Get a list of dice that is selected, subset of the list of current dice.
     */
    std::vector<Die> getSelectedDice();
    /**
     * Get a list of dice that is currently in the screen.
     */
    std::vector<Die> getCurrentDice();
    /**
     * Check if there is any die sprite of this im
     */
    bool hasDieSprite(sf::Int32 id);
    void animate_diceUsed(std::vector<sf::Int32> dice);
    DieSprite getAndRemoveDieSprite(sf::Int32 id);
    DieSprite* getDieSprite(sf::Vector2f mousePos);
    DieSprite* getDieSprite(const sf::Int32 id);
    ////////// End of Dice Sprites Stuffs /////////
    

    //////////// Unit Sprites Stuffs ///////////
    // there should only be two unit
    std::vector<UnitSprite> _units;
    void updateUnits();
    /////////// End Of Unit Sprites Stuffs //////////
    
    ///////// GAME STATE //////
    GameScreenState _currentState;
    PlayerRole::ePlayerRole _currentPlayer;
    Battle& _battle;
    PlayerRole::ePlayerRole _role;
    /// ANIMATOR
    SimpleAnimator _animator;
    float _animationTimer1;
    float _animationTimer2;

    ///// Buttons //////
    zf::Button rollButton;
    zf::Button doneButton;
    zf::Button _rulesButton;
    ///// Dialog /////
    sf::Sprite resultDialog;
    sf::Text resultText;
    zf::Button backToSetupButton;

    /// Updater and Viewer
    GameScreenViewer _viewer;
    GeneralUpdater _updater;

    // exit timer
    float exitTimer;
};
#endif
