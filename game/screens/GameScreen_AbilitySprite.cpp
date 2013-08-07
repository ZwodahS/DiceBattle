#include "GameScreen.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"
GameScreen::AbilitySprite::AbilitySprite(Ability& a, std::vector<sf::Sprite> c, std::vector<sf::Sprite> es, std::vector<sf::Text> et, sf::Sprite bg, sf::Text nt)
    :ability(&a), cost(c), effectsSymbol(es), effectsText(et), nameText(nt), background(bg), clickBound(0,0,480,40)
{
    setPosition(sf::Vector2f(0,0));
}

const int AbilitySprite_CostStart_X = 10;
const int AbilitySprite_CostSize_X = 24;
const int AbilitySprite_CostOffset_X = 0;
const int AbilitySprite_CostStart_Y = 0;
const int AbilitySprite_CostSize_Y = 24;

const int AbilitySprite_EffectSymbolStart_X = 240;
const int AbilitySprite_EffectSymbolOffset_X = 50;
const int AbilitySprite_EffectSymbolTextSpacingX = 0;
const int AbilitySprite_EffectSymbolTextSpacingY = 0;

const int AbilitySprite_NameX = 270;
const int AbilitySprite_NameY = 18;
void GameScreen::AbilitySprite::setPosition(sf::Vector2f position)
{
    clickBound.left = position.x;
    clickBound.top = position.y;
    for(int i = 0 ; i < cost.size() ; i++)
    {
        cost[i].setPosition(position + sf::Vector2f(AbilitySprite_CostStart_X + (i * (AbilitySprite_CostSize_X + AbilitySprite_CostOffset_X)), AbilitySprite_CostStart_Y));
    }
    // if this is constructed properly, each effect symbol will have a corresponding text
    for(int i = 0 ; i < effectsSymbol.size() ; i++)
    {
        effectsSymbol[i].setPosition(position + sf::Vector2f(AbilitySprite_EffectSymbolStart_X + (i * (AbilitySprite_EffectSymbolOffset_X)), AbilitySprite_CostStart_Y));
        effectsText[i].setPosition(position + sf::Vector2f(AbilitySprite_EffectSymbolStart_X + (i * (AbilitySprite_EffectSymbolOffset_X)) + AbilitySprite_EffectSymbolTextSpacingX, AbilitySprite_CostStart_Y + AbilitySprite_EffectSymbolTextSpacingY));
    }
    nameText.setPosition(position + sf::Vector2f(AbilitySprite_NameX, AbilitySprite_NameY));
}

void GameScreen::AbilitySprite::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    window.draw(background);
    for(std::vector<sf::Sprite>::iterator it = cost.begin() ; it != cost.end() ; ++it)
    {
        window.draw(*it); 
    }
    for(std::vector<sf::Sprite>::iterator it = effectsSymbol.begin() ; it != effectsSymbol.end() ; ++it)
    {
        window.draw(*it); 
    }
    for(std::vector<sf::Text>::iterator it = effectsText.begin() ; it != effectsText.end() ; ++it)
    {
        window.draw(*it); 
    }
    window.draw(nameText);
}

void GameScreen::AbilitySprite::update(sf::RenderWindow& window, const sf::Time& delta)
{

}

GameScreen::AbilitySprite GameScreen::makeAbilitySprite(Ability& ability)
{
    std::vector<sf::Sprite> costs;
    for(std::vector<DieFace::eDieFace>::const_iterator it = ability.costs.begin() ; it != ability.costs.end() ; ++it)
    {
        sf::Sprite dieFace = _game.assets.getSprite(*it);
        dieFace.setScale(0.8,0.8);    
        costs.push_back(dieFace);
    }
    std::vector<sf::Sprite> effectsSymbol;
    std::vector<sf::Text> effectsText;
    for(std::vector<AbilityEffect>::const_iterator it = ability.effects.begin() ; it != ability.effects.end() ; ++it)
    {
        sf::Sprite effectSymbol = _game.assets.getSprite((*it).type);
        sf::Text text(zf::toString((*it).value), _game.assets.gameScreenAssets.abilityFont, 24);
        text.setColor(sf::Color(0,0,0,200));
        effectSymbol.setScale(0.8,0.8);
        effectsSymbol.push_back(effectSymbol);
        effectsText.push_back(text);
    }
    sf::Sprite background = _game.assets.gameScreenAssets.abilityStrip.createSprite();
    sf::Text nameText(ability.name, _game.assets.gameScreenAssets.abilityFont, 16);
    nameText.setColor(sf::Color(0,0,0,180));
    return AbilitySprite(ability, costs, effectsSymbol, effectsText, background, nameText);
}
