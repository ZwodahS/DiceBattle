#include "Assets.hpp"
sf::Sprite Assets::getSprite(DieFace::eDieFace f)
{
    switch(f)
    {
        case DieFace::Sword : return icons.sword.createSprite();
        case DieFace::Shield : return icons.shield.createSprite();
        case DieFace::Heal : return icons.heal.createSprite();
        case DieFace::Fire : return icons.fire.createSprite();
        case DieFace::Ice : return icons.ice.createSprite();
        case DieFace::Shock : return icons.shock.createSprite();
        default : return sf::Sprite();
    }
}

sf::Sprite Assets::getSprite(AbilityType::eAbilityType t)
{
    switch(t)
    {
        case AbilityType::PhysicalDamage : return icons.physical.createSprite();
        case AbilityType::MagicalDamage : return icons.magical.createSprite();
        case AbilityType::Shield : return icons.armor.createSprite();
        case AbilityType::Heal : return icons.heart.createSprite();
        case AbilityType::Burn : return icons.burnt.createSprite();
        case AbilityType::Freeze : return icons.frozen.createSprite();
        case AbilityType::Shock : return icons.shock.createSprite();
        default: return sf::Sprite();
    }
}
