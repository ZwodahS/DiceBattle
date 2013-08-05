#include "Game.hpp"

void Game::loadAssets()
{
    /// master sprite sheet
    assets.master1.create(1024,1024);
    assets.masterS1.create(&assets.master1,sf::IntRect(0,0,1024,1024));
    //// placeholder spritesheet
    assets.placeholderTexture.create(1200,1200);
    
    sf::Image image;
    //assets.scoreFont.loadFromFile("assets/fonts/sofachrome.ttf");
    
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
}
