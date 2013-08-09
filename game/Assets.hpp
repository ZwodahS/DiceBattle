#ifndef _GAME_ASSETS_
#define _GAME_ASSETS_
#include "../z_framework/zf_sfml/SpriteSheet.hpp"
#include "../z_framework/zf_sfml/TextureRegion.hpp"
#include "constants/DieFace.hpp"
#include "constants/AbilityType.hpp"

struct IconAssets
{
    TextureRegion sword;
    TextureRegion magical;
    TextureRegion physical; 
    
    TextureRegion armor;
    TextureRegion shield;

    TextureRegion burnt;
    TextureRegion fire;

    TextureRegion frozen;
    TextureRegion ice;

    TextureRegion stunned;
    TextureRegion shock;

    TextureRegion heart;
    TextureRegion heal;
    
    SpriteSheet spriteSheet;
};

struct GameScreenAssets
{
    //270 x 100
    TextureRegion characterSheet;
    //480 x 40
    TextureRegion abilityStrip;
    TextureRegion die;
    TextureRegion rollButton;
    TextureRegion rollButtonSelected;
    TextureRegion doneButton;
    TextureRegion doneButtonSelected;
    sf::Font abilityFont;
    SpriteSheet spriteSheet;
};

// Some placeholder assets that can be use to get started
struct PlaceHolderAssets
{
    TextureRegion sq8;
    TextureRegion sq16;
    TextureRegion sq24;
    TextureRegion sq32;
    TextureRegion sq38;
    TextureRegion sq48;
    TextureRegion sq100;
    TextureRegion sq150;
    SpriteSheet spriteSheet;
};

struct Assets
{
    PlaceHolderAssets placeHolder;
    IconAssets icons;
    GameScreenAssets gameScreenAssets;
    sf::Texture master1;
    SpriteSheet masterS1;
    sf::Texture placeholderTexture;
    sf::Sprite getSprite(DieFace::eDieFace);
    sf::Sprite getSprite(AbilityType::eAbilityType);
};
#endif
