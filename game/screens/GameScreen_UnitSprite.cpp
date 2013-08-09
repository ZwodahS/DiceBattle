#include "GameScreen.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"

const int UnitSprite_NameX = 10;
const int UnitSprite_NameY = 0;
const int UnitSprite_HeartX = 5;
const int UnitSprite_HeartY = 17;
const int UnitSprite_HeartTextX = 50;
const int UnitSprite_HeartTextY = 17;
const int UnitSprite_ArmorX = 130;
const int UnitSprite_ArmorY = 17;
const int UnitSprite_ArmorTextX = 175;
const int UnitSprite_ArmorTextY = 17;
const int UnitSprite_EffectsX[] = {10,70,130,190};
const int UnitSprite_EffectsY[] = {55,55,55,55};
const int UnitSprite_EffectsTextX[] = {50,110,170,230};
const int UnitSprite_EffectsTextY[] = {55,55,55,55};

GameScreen::UnitSprite::UnitSprite(Unit& u, sf::Sprite bg, sf::Sprite heart, sf::Sprite armor, sf::Sprite stunned, sf::Sprite burnt, sf::Sprite frozen, sf::Text name, sf::Text currentHp, sf::Text shield, sf::Text generic)
    :unit(&u), background(bg), heartSprite(heart), armorSprite(armor), stunnedSprite(stunned), burntSprite(burnt), frozenSprite(frozen), nameText(name), currentHpText(currentHp), shieldText(shield), genericText(generic), clickBound(0,0,270,100)
{
    effects.push_back(stunnedSprite);
    effectsText.push_back(genericText);
    effects.push_back(burntSprite);
    effectsText.push_back(genericText);
    effects.push_back(frozenSprite);
    effectsText.push_back(genericText);
    setActive(false);
}

void GameScreen::UnitSprite::setPosition(sf::Vector2f position)
{
    clickBound.left = position.x;
    clickBound.top = position.y;
    background.setPosition(position); 
    nameText.setPosition(position + sf::Vector2f(UnitSprite_NameX,UnitSprite_NameY));
    heartSprite.setPosition(position + sf::Vector2f(UnitSprite_HeartX, UnitSprite_HeartY));
    currentHpText.setPosition(position + sf::Vector2f(UnitSprite_HeartTextX, UnitSprite_HeartTextY));
    armorSprite.setPosition(position + sf::Vector2f(UnitSprite_ArmorX, UnitSprite_ArmorY));
    shieldText.setPosition(position + sf::Vector2f(UnitSprite_ArmorTextX, UnitSprite_ArmorTextY));
    for(int i = 0; i < effects.size() ; i++)
    {
        effects[i].setPosition(position + sf::Vector2f(UnitSprite_EffectsX[i], UnitSprite_EffectsY[i]));
        effectsText[i].setPosition(position + sf::Vector2f(UnitSprite_EffectsTextX[i], UnitSprite_EffectsTextY[i]));
    }
}

void GameScreen::UnitSprite::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    window.draw(background);
    window.draw(nameText);
    window.draw(heartSprite);
    window.draw(currentHpText);
    window.draw(armorSprite);
    window.draw(shieldText);
    for(int i = 0 ; i < effects.size(); i++)
    {
        window.draw(effects[i]);
        window.draw(effectsText[i]);
    }
}

void GameScreen::UnitSprite::update(sf::RenderWindow& window, const sf::Time& delta)
{
    
}

void GameScreen::UnitSprite::resetUnitStats()
{

}

GameScreen::UnitSprite GameScreen::makeUnitSprite(Unit& unit)
{
    sf::Sprite bg = _game.assets.gameScreenAssets.characterSheet.createSprite();
    sf::Sprite heart = _game.assets.icons.heart.createSprite();
    sf::Sprite armor = _game.assets.icons.armor.createSprite();
    sf::Sprite stunned = _game.assets.icons.stunned.createSprite();
    sf::Sprite burnt = _game.assets.icons.burnt.createSprite();
    sf::Sprite frozen = _game.assets.icons.frozen.createSprite();

    sf::Text nameText(unit.name, _game.assets.gameScreenAssets.abilityFont, 16);
    nameText.setColor(sf::Color::Black);
    sf::Text currentHp(zf::toString(unit.currentHp), _game.assets.gameScreenAssets.abilityFont, 32);
    currentHp.setColor(sf::Color::Black);
    sf::Text shieldText(zf::toString(unit.shieldCounter), _game.assets.gameScreenAssets.abilityFont, 32);
    shieldText.setColor(sf::Color::Black);
    sf::Text genericText(zf::toString(0), _game.assets.gameScreenAssets.abilityFont, 24);
    genericText.setColor(sf::Color::Red);
    return UnitSprite(unit, bg, heart, armor, stunned, burnt, frozen, nameText, currentHp, shieldText, genericText);
}

sf::Vector2f GameScreen::UnitSprite::getPosition()
{
    return sf::Vector2f(clickBound.left, clickBound.top);
}

void GameScreen::UnitSprite::setActive(bool active)
{
    if(active)
    {
        background.setColor(sf::Color(230,230,140));
    }
    else
    {
        background.setColor(sf::Color(140,140,85));
    }
}
