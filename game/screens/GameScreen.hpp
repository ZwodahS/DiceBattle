#ifndef _GAME_SCREENS_GAMESCREEN_H_
#define _GAME_SCREENS_GAMESCREEN_H_
#include "Screen.hpp"
#include "../constants.hpp"
#include "../messages/g_messages.hpp"
#include "../../z_framework/zf_sfml/animations/SimpleAnimator.hpp"
#include <vector>
class GameViewer;
class GameUpdater;
class Game;
class Battle;
class Ability;
class GameScreen : public Screen 
{
public:

    static const float RandomizerChangeRate = 0.1;
    static const sf::Int32 DiceSize = 48;
    GameScreen(Game& game, Battle& battle, PlayerRole::ePlayerRole role, GameViewer& viewer, GameUpdater& updater);
    ~GameScreen();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta);

    /**
     * Used by GameScreenViewer
     */
    void sendMessage(DB_GameStartMessage& message);
    void sendMessage(DB_ActiveTurnMessage& message);
    void sendMessage(DB_AskForActionMessage& message);
    void sendMessage(DB_AbilityUsedMessage& message);
    void sendMessage(DB_DiceRolledResultMessage& message);
    void sendMessage(DB_EndTurnMessage& message);
    void sendMessage(DB_EndGameMessage& message);
private:
    ///// all the sprites of the game /////
    //////// DIE SPRITE /////////
    class DieSprite : public iAnimatable
    {
    public:
        DieSprite(sf::Int32 id, std::vector<sf::Sprite> faces, sf::Sprite dieBorder);
        sf::Int32 id;
        std::vector<sf::Sprite> faces;
        sf::Sprite dieBorder;
        DieFace::eDieFace currentFace;
        float randomizerTimer;
        sf::FloatRect clickBound;
        bool random;
        bool visible;
        void setRandom(bool r);
        void setVisible(bool v);
        void update(sf::RenderWindow& window, const sf::Time& delta);
        void draw(sf::RenderWindow& window, const sf::Time& delta);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
    };
    DieSprite makeDie(sf::Int32 id);
    ///////// END OF DIESPRITE ////////
    //////// Unit Sprite //////
    class UnitSprite
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
        sf::Text genericText;
        std::vector<sf::Sprite> effects;
        std::vector<sf::Text> effectsText;
        void setPosition(sf::Vector2f position);
        void draw(sf::RenderWindow& window, const sf::Time& delta);
        void update(sf::RenderWindow& window, const sf::Time& delta);
        void resetUnitStats();
        sf::FloatRect clickBound;
    }; 
    UnitSprite makeUnitSprite(Unit& unit);
    //////// End of Unit Sprite /////
    /////// Ability Sprite //////
    class AbilitySprite : iAnimatable
    {
    public:
        AbilitySprite(Ability& ability, std::vector<sf::Sprite> cost, std::vector<sf::Sprite> effectsSymbol, std::vector<sf::Text> effectsText, sf::Sprite background, sf::Text nameText);
        Ability* ability;
        std::vector<sf::Sprite> cost; 
        std::vector<sf::Sprite> effectsSymbol;
        std::vector<sf::Text> effectsText;
        sf::Text nameText;
        sf::Sprite background;
        sf::FloatRect clickBound;
        /**
         * Set the position of this ability sprite. It defines the top left corner of the sprite.
         */
        void setPosition(sf::Vector2f position);

        void draw(sf::RenderWindow& window, const sf::Time& delta);
        void update(sf::RenderWindow& window, const sf::Time& delta);
    };
    AbilitySprite makeAbilitySprite(Ability& ability);
    /////// End of Ability Sprite //////

    std::vector<AbilitySprite> _abilitySprites;

    Battle& _battle;
    PlayerRole::ePlayerRole& _role;
    GameViewer& _viewer;
    GameUpdater& _updater;

    std::vector<DieSprite> _diceSprites;
    // there should only be two unit
    std::vector<UnitSprite> _units;
};
#endif
