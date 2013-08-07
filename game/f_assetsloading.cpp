#include "Game.hpp"

void Game::loadAssets()
{
    /// master sprite sheet
    assets.master1.create(1024,1024);
    assets.masterS1.create(&assets.master1,sf::IntRect(0,0,1024,1024));
    //// placeholder spritesheet
    assets.placeholderTexture.create(1200,1200);
    
    sf::Image image;
    assets.gameScreenAssets.abilityFont.loadFromFile("data/fonts/upheavtt.ttf");
    
    //create the placeholder spritesheet
    assets.placeHolder.spriteSheet.create(&assets.placeholderTexture,sf::IntRect(0,0,1000,1000));
    // the 100 by 100 square
    image.loadFromFile("data/graphics/placeholder/squares/solid/100x100.png");
    assets.placeHolder.sq100 = assets.placeHolder.spriteSheet.createRegion(image,0,0);
    for(int r = 0 ; r < 12 ; r++)
    {
        for(int c = 0 ; c < 12 ; c++)
        {
            assets.placeHolder.spriteSheet.createRegion(image,r*100,c*100);
        }
    }
    assets.placeHolder.sq8 = assets.placeHolder.spriteSheet.createRegion(sf::IntRect(0,0,8,8));
    assets.placeHolder.sq16 = assets.placeHolder.spriteSheet.createRegion(sf::IntRect(0,0,16,16));
    assets.placeHolder.sq24 = assets.placeHolder.spriteSheet.createRegion(sf::IntRect(0,0,24,24));
    assets.placeHolder.sq32 = assets.placeHolder.spriteSheet.createRegion(sf::IntRect(0,0,32,32));
    assets.placeHolder.sq48 = assets.placeHolder.spriteSheet.createRegion(sf::IntRect(0,0,48,48));
    assets.placeHolder.sq38 = assets.placeHolder.spriteSheet.createRegion(sf::IntRect(0,0,38,38));
    assets.placeHolder.sq150 = assets.placeHolder.spriteSheet.createRegion(sf::IntRect(0,0,150,150));


    assets.icons.spriteSheet = assets.masterS1.createSubSheet(sf::Vector2i(0,0), sf::IntRect(0,0,48,48), 0, 20);
    
    image.loadFromFile("data/graphics/icons/sword.png");
    assets.icons.sword = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/magical.png");
    assets.icons.magical = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/physical.png");
    assets.icons.physical = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/armor.png");
    assets.icons.armor = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/shield.png");
    assets.icons.shield = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/burnt.png");
    assets.icons.burnt = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/fire.png");
    assets.icons.fire = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/frozen.png");
    assets.icons.frozen = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/ice.png");
    assets.icons.ice = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/stunned.png");
    assets.icons.stunned = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/shock.png");
    assets.icons.shock = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/heart.png");
    assets.icons.heart = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/icons/heal.png");
    assets.icons.heal = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/die.png");
    assets.icons.die = assets.icons.spriteSheet.createRegion(image);

    image.loadFromFile("data/graphics/abilityStrip.png");
    assets.gameScreenAssets.abilityStrip = assets.masterS1.createRegion(image, 0, 50);
    image.loadFromFile("data/graphics/charactersheet.png");
    assets.gameScreenAssets.characterSheet = assets.masterS1.createRegion(image,0, 100);
}
