#include "Game.hpp"

void Game::loadAssets()
{
    /// master sprite sheet
    assets.master1.create(1280,1280);
    assets.masterS1.create(&assets.master1,sf::IntRect(0,0,1280,1280));
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

    image.loadFromFile("data/graphics/background.png");
    assets.background = assets.masterS1.createRegion(image,0,0);

    assets.icons.spriteSheet = assets.masterS1.createSubSheet(sf::Vector2i(0,480), sf::IntRect(0,0,34,34), 0, 20);
    
    image.loadFromFile("data/graphics/gamescreen/icons/sword.png");
    assets.icons.sword = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/magical.png");
    assets.icons.magical = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/physical.png");
    assets.icons.physical = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/armor.png");
    assets.icons.armor = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/shield.png");
    assets.icons.shield = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/burnt.png");
    assets.icons.burnt = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/fire.png");
    assets.icons.fire = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/frozen.png");
    assets.icons.frozen = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/ice.png");
    assets.icons.ice = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/stunned.png");
    assets.icons.stunned = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/shock.png");
    assets.icons.shock = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/heart.png");
    assets.icons.heart = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/icons/heal.png");
    assets.icons.heal = assets.icons.spriteSheet.createRegion(image);
    image.loadFromFile("data/graphics/gamescreen/die.png");
    assets.gameScreenAssets.die = assets.masterS1.createRegion(image,640,0);
    assets.gameScreenAssets.dieSelectionBorder = assets.placeHolder.spriteSheet.createRegion(sf::IntRect(0,0,48,48));
    assets.gameScreenAssets.dieSelectionBorder.defaultColor = sf::Color(230,40,50);

    image.loadFromFile("data/graphics/gamescreen/abilitystrip.png");
    assets.gameScreenAssets.abilityStrip = assets.masterS1.createRegion(image,0, 514);
    image.loadFromFile("data/graphics/gamescreen/gamerollbutton.png");
    assets.gameScreenAssets.rollButton = assets.masterS1.createRegion(image,0,554);
    assets.gameScreenAssets.rollButtonSelected = assets.masterS1.createRegion(sf::IntRect(0,554,200,70));
    assets.gameScreenAssets.rollButtonSelected.defaultColor = sf::Color(255,255,170,255);
    image.loadFromFile("data/graphics/gamescreen/gamedonebutton.png");
    assets.gameScreenAssets.doneButton = assets.masterS1.createRegion(image,200,554);
    assets.gameScreenAssets.doneButtonSelected = assets.masterS1.createRegion(sf::IntRect(200,554,200,70));
    assets.gameScreenAssets.doneButtonSelected.defaultColor = sf::Color(255,255,170,255);
    image.loadFromFile("data/graphics/gamescreen/charactersheet.png");
    assets.gameScreenAssets.characterSheet = assets.masterS1.createRegion(image,700, 0);
    
    image.loadFromFile("data/graphics/gamescreen/resultdialog.png");
    assets.gameScreenAssets.resultDialogBox = assets.masterS1.createRegion(image, 640, 100);
    
    image.loadFromFile("data/graphics/okButton.png");
    assets.gameScreenAssets.backToSetupButton = assets.masterS1.createRegion(image, 500, 514);
    assets.gameScreenAssets.backToSetupButtonSelected = assets.masterS1.createRegion(sf::IntRect(500,514,100,30));
    assets.gameScreenAssets.backToSetupButtonSelected.defaultColor = sf::Color(255,255,170);
    image.loadFromFile("data/graphics/gamescreen/lock.png");
    assets.gameScreenAssets.lockIcon = assets.masterS1.createRegion(image,640,60); 

    ////////////////// Setup Screen ///////////////
    assets.setupScreenAssets.nameBox = assets.placeHolder.spriteSheet.createRegion(sf::IntRect(0,0,200,30));
    image.loadFromFile("data/graphics/setupscreen/startButton.png");
    assets.setupScreenAssets.startButton = assets.masterS1.createRegion(image, 400, 624);
    assets.setupScreenAssets.startButtonSelected = assets.masterS1.createRegion(sf::IntRect(400, 624, 100, 30));
    assets.setupScreenAssets.startButtonSelected.defaultColor = sf::Color(255,255,170,255);

    //////////////// Main Screen /////////////////
    image.loadFromFile("data/graphics/mainscreen/bigJoinButton.png");
    assets.mainScreenAssets.joinButton = assets.masterS1.createRegion(image, 0, 654);
    image.loadFromFile("data/graphics/mainscreen/bigHostButton.png");
    assets.mainScreenAssets.hostButton = assets.masterS1.createRegion(image, 200, 654);
    image.loadFromFile("data/graphics/mainscreen/bigLocalButton.png");
    assets.mainScreenAssets.localButton = assets.masterS1.createRegion(image, 400, 654);
    
    image.loadFromFile("data/graphics/mainscreen/dialog.png");
    assets.mainScreenAssets.dialog.background = assets.masterS1.createRegion(image, 640, 200);
    image.loadFromFile("data/graphics/mainscreen/ipbox.png");
    assets.mainScreenAssets.dialog.ipBg = assets.masterS1.createRegion(image, 940, 100);
    image.loadFromFile("data/graphics/mainscreen/namebox.png");
    assets.mainScreenAssets.dialog.nameBg = assets.masterS1.createRegion(image, 640, 400);
    image.loadFromFile("data/graphics/mainscreen/portbox.png");
    assets.mainScreenAssets.dialog.portBg = assets.masterS1.createRegion(image, 640, 430);
    image.loadFromFile("data/graphics/mainscreen/joinButton.png");
    assets.mainScreenAssets.dialog.joinButton = assets.masterS1.createRegion(image, 100, 624);
    assets.mainScreenAssets.dialog.joinButtonSelected = assets.masterS1.createRegion(sf::IntRect(100,624,100,30));
    assets.mainScreenAssets.dialog.joinButtonSelected.defaultColor = sf::Color(255,255,170,255);
    image.loadFromFile("data/graphics/mainscreen/hostButton.png");
    assets.mainScreenAssets.dialog.hostButton = assets.masterS1.createRegion(image, 200, 624);
    assets.mainScreenAssets.dialog.hostButtonSelected = assets.masterS1.createRegion(sf::IntRect(200,624,100,30));
    assets.mainScreenAssets.dialog.hostButtonSelected.defaultColor = sf::Color(255,255,170,255);
    image.loadFromFile("data/graphics/mainscreen/cancelButton.png");
    assets.mainScreenAssets.dialog.cancelButton = assets.masterS1.createRegion(image, 300, 624);
    assets.mainScreenAssets.dialog.cancelButtonSelected = assets.masterS1.createRegion(sf::IntRect(300,624,100,30));
    assets.mainScreenAssets.dialog.cancelButtonSelected.defaultColor = sf::Color(255,255,170,255);
}
