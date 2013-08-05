#ifndef _GAME_ASSETS_
#define _GAME_ASSETS_
#include "../z_framework/zf_sfml/SpriteSheet.hpp"
#include "../z_framework/zf_sfml/TextureRegion.hpp"


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
    sf::Texture master1;
    SpriteSheet masterS1;
    sf::Texture placeholderTexture;
};
#endif
