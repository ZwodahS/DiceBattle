#include "HelpScreen.hpp"
#include "../Game.hpp"

HelpScreen::HelpScreen(Game& game)
    :Screen(game), _currentPage(1)
    , _nextButton(game.assets.nextButtonSelected.createSprite(), game.assets.nextButton.createSprite(), sf::FloatRect(0,0,25,30))
    , _previousButton(game.assets.previousButtonSelected.createSprite(), game.assets.previousButton.createSprite(), sf::FloatRect(0,0,25,30))
    , _closeButton(game.assets.closeButtonSelected.createSprite(), game.assets.closeButton.createSprite(), sf::FloatRect(0,0,30,30))
{
    loadPageOne();
    loadPageTwo();
    loadPageThree();
    _nextButton.setPosition(sf::Vector2f(530,440));
    _previousButton.setPosition(sf::Vector2f(500,440));
    _closeButton.setPosition(sf::Vector2f(580,440));
}

HelpScreen::~HelpScreen()
{
}

void HelpScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    _closeButton.draw(window, delta);
    if(_currentPage == 1)
    {
        for(std::vector<sf::Sprite>::iterator it = _pageOneSprites.begin() ; it != _pageOneSprites.end() ; ++it)
        {
            window.draw(*it); 
        }
        for(std::vector<sf::Text>::iterator it = _pageOneTexts.begin() ; it != _pageOneTexts.end() ; ++it)
        {
            window.draw(*it); 
        }
        _nextButton.draw(window,delta);
    }
    else if(_currentPage == 2)
    {
        for(std::vector<sf::Sprite>::iterator it = _pageTwoSprites.begin() ; it != _pageTwoSprites.end() ; ++it)
        {
            window.draw(*it); 
        }
        for(std::vector<sf::Text>::iterator it = _pageTwoTexts.begin() ; it != _pageTwoTexts.end() ; ++it)
        {
            window.draw(*it); 
        }
        _previousButton.draw(window,delta);
        _nextButton.draw(window,delta);
    }
    else if(_currentPage == 3)
    {
        for(std::vector<sf::Sprite>::iterator it = _pageThreeSprites.begin() ; it != _pageThreeSprites.end() ; ++it)
        {
            window.draw(*it); 
        }
        for(std::vector<sf::Text>::iterator it = _pageThreeTexts.begin() ; it != _pageThreeTexts.end() ; ++it)
        {
            window.draw(*it); 
        }
        _previousButton.draw(window,delta);
    }
}

void HelpScreen::update(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput)
{
    zf::Mouse& mouse = _game.mouse;
    sf::Vector2f mousePosF = mouse.getWorldPosition(window);
    _nextButton.updateSelection(mousePosF);
    _previousButton.updateSelection(mousePosF);
    _closeButton.updateSelection(mousePosF);
    if(mouse.left.thisPressed && handleInput)
    {
        if(_nextButton.clickBound.contains(mousePosF))
        {
            nextPage();
        }
        else if(_previousButton.clickBound.contains(mousePosF))
        {
            previousPage();
        }
        else if(_closeButton.clickBound.contains(mousePosF))
        {
            _game.toggleShowHelp();
        }
    }
}

void HelpScreen::textInput(char c)
{
}


void HelpScreen::loadPageOne()
{
    // not yet loaded
    if(_pageOneSprites.size() == 0)
    {
        sf::Text tmp = sf::Text(" ", _game.assets.gameScreenAssets.abilityFont, 18);
        sf::Sprite spriteTmp;
        tmp.setColor(sf::Color::Black);
        tmp.setPosition(sf::Vector2f(20,20));
        tmp.setString("The objective of the game is to defeat your opponent");
        _pageOneTexts.push_back(tmp);
        tmp.setString("using the ability that you have.");
        tmp.setPosition(sf::Vector2f(20,40));
        _pageOneTexts.push_back(tmp);
        tmp.setString("Each ability can be activated using the dice that you rolled.");
        tmp.setPosition(sf::Vector2f(20,70));
        _pageOneTexts.push_back(tmp);
        tmp.setString("Dice are 6-sided and can have the following faces");
        tmp.setPosition(sf::Vector2f(20,100));
        _pageOneTexts.push_back(tmp);
        spriteTmp = _game.assets.icons.sword.createSprite();
        spriteTmp.setPosition(sf::Vector2f(20, 130));
        _pageOneSprites.push_back(spriteTmp);
        spriteTmp = _game.assets.icons.shield.createSprite();
        spriteTmp.setPosition(sf::Vector2f(60, 130));
        _pageOneSprites.push_back(spriteTmp);
        spriteTmp = _game.assets.icons.fire.createSprite();
        spriteTmp.setPosition(sf::Vector2f(100, 130));
        _pageOneSprites.push_back(spriteTmp);
        spriteTmp = _game.assets.icons.ice.createSprite();
        spriteTmp.setPosition(sf::Vector2f(140, 130));
        _pageOneSprites.push_back(spriteTmp);
        spriteTmp = _game.assets.icons.shock.createSprite();
        spriteTmp.setPosition(sf::Vector2f(180, 130));
        _pageOneSprites.push_back(spriteTmp);
        spriteTmp = _game.assets.icons.heal.createSprite();
        spriteTmp.setPosition(sf::Vector2f(220, 130));
        _pageOneSprites.push_back(spriteTmp);
        tmp.setString("In the default rule, there will be 6 dice, and all");
        tmp.setPosition(sf::Vector2f(20, 180));
        _pageOneTexts.push_back(tmp);
        tmp.setString("of them will have one of each face");
        tmp.setPosition(sf::Vector2f(20, 200));
        _pageOneTexts.push_back(tmp);
    }
}

void HelpScreen::loadPageTwo()
{
    if(_pageTwoSprites.size() == 0)
    {
        sf::Text tmp = sf::Text(" ", _game.assets.gameScreenAssets.abilityFont, 18);
        sf::Sprite spriteTmp;
        tmp.setColor(sf::Color::Black);
        tmp.setPosition(sf::Vector2f(20,20));
        tmp.setString("Each ability will look something like this");
        _pageTwoTexts.push_back(tmp);
        // show the level 3 sword
        spriteTmp = _game.assets.gameScreenAssets.abilityStrip.createSprite();
        spriteTmp.setPosition(sf::Vector2f(20, 50));
        _pageTwoSprites.push_back(spriteTmp);
        spriteTmp = _game.assets.icons.sword.createSprite();
        spriteTmp.setPosition(sf::Vector2f(20, 50) + sf::Vector2f(10, 2));
        _pageTwoSprites.push_back(spriteTmp);
        spriteTmp.setPosition(sf::Vector2f(20, 50) + sf::Vector2f(34, 2));
        _pageTwoSprites.push_back(spriteTmp);
        spriteTmp.setPosition(sf::Vector2f(20, 50) + sf::Vector2f(58, 2));
        _pageTwoSprites.push_back(spriteTmp);
        spriteTmp = _game.assets.icons.physical.createSprite();
        spriteTmp.setPosition(sf::Vector2f(20, 50) + sf::Vector2f(240, 2));
        _pageTwoSprites.push_back(spriteTmp);
        tmp.setString("9");
        tmp.setCharacterSize(24);
        tmp.setPosition(sf::Vector2f(20, 50) + sf::Vector2f(280, 2));
        _pageTwoTexts.push_back(tmp);
        tmp.setCharacterSize(18);
        tmp.setString("The left of the ability show the icons that is required");
        tmp.setPosition(sf::Vector2f(20,90));
        _pageTwoTexts.push_back(tmp);
        tmp.setString("to activate this ability");
        tmp.setPosition(sf::Vector2f(20,110));
        _pageTwoTexts.push_back(tmp);
        tmp.setString("The right side shows the effects for this ability.");
        tmp.setPosition(sf::Vector2f(20,130));
        _pageTwoTexts.push_back(tmp);

        spriteTmp = _game.assets.icons.physical.createSprite();
        spriteTmp.setPosition(sf::Vector2f(20,180));
        _pageTwoSprites.push_back(spriteTmp);
        tmp.setString("Physical damage.");
        tmp.setPosition(sf::Vector2f(70, 170));
        _pageTwoTexts.push_back(tmp);
        tmp.setString("Number = damage dealt");
        tmp.setPosition(sf::Vector2f(70, 190));
        _pageTwoTexts.push_back(tmp);

        spriteTmp = _game.assets.icons.magical.createSprite();
        spriteTmp.setPosition(sf::Vector2f(100,220));
        _pageTwoSprites.push_back(spriteTmp);
        tmp.setString("Magical damage. Ignore armor");
        tmp.setPosition(sf::Vector2f(150, 210));
        _pageTwoTexts.push_back(tmp);
        tmp.setString("Number = Damage dealt");
        tmp.setPosition(sf::Vector2f(150, 230));
        _pageTwoTexts.push_back(tmp);

        spriteTmp = _game.assets.icons.armor.createSprite();
        spriteTmp.setPosition(sf::Vector2f(20,260));
        _pageTwoSprites.push_back(spriteTmp);
        tmp.setString("Increase armor");
        tmp.setPosition(sf::Vector2f(70, 250));
        _pageTwoTexts.push_back(tmp);
        tmp.setString("Number = Armor gained");
        tmp.setPosition(sf::Vector2f(70, 270));
        _pageTwoTexts.push_back(tmp);

        spriteTmp = _game.assets.icons.burnt.createSprite();
        spriteTmp.setPosition(sf::Vector2f(100,300));
        _pageTwoSprites.push_back(spriteTmp);
        tmp.setString("Burn the enemy. Increase their burn counter");
        tmp.setPosition(sf::Vector2f(150, 290));
        _pageTwoTexts.push_back(tmp);
        tmp.setString("Number = Amount increased");
        tmp.setPosition(sf::Vector2f(150, 310));
        _pageTwoTexts.push_back(tmp);

        spriteTmp = _game.assets.icons.frozen.createSprite();
        spriteTmp.setPosition(sf::Vector2f(20,340));
        _pageTwoSprites.push_back(spriteTmp);
        tmp.setString("Freeze enemy. Causes dice to be frozen.");
        tmp.setPosition(sf::Vector2f(70, 330));
        _pageTwoTexts.push_back(tmp);
        tmp.setString("Number = Number of dice froze");
        tmp.setPosition(sf::Vector2f(70, 350));
        _pageTwoTexts.push_back(tmp);

        spriteTmp = _game.assets.icons.stunned.createSprite();
        spriteTmp.setPosition(sf::Vector2f(100,380));
        _pageTwoSprites.push_back(spriteTmp);
        tmp.setString("Stunned enemy. Increase Stun counter");
        tmp.setPosition(sf::Vector2f(150, 370));
        _pageTwoTexts.push_back(tmp);
        tmp.setString("Number = Amount increased");
        tmp.setPosition(sf::Vector2f(150, 390));
        _pageTwoTexts.push_back(tmp);

        spriteTmp = _game.assets.icons.heart.createSprite();
        spriteTmp.setPosition(sf::Vector2f(20,420));
        _pageTwoSprites.push_back(spriteTmp);
        tmp.setString("Heal self.");
        tmp.setPosition(sf::Vector2f(70, 410));
        _pageTwoTexts.push_back(tmp);
        tmp.setString("Number = Amount of health gained.");
        tmp.setPosition(sf::Vector2f(70, 430));
        _pageTwoTexts.push_back(tmp);

    }
}

void HelpScreen::loadPageThree()
{
    if(_pageThreeSprites.size() == 0)
    {
        sf::Text tmp = sf::Text(" ", _game.assets.gameScreenAssets.abilityFont, 18);
        sf::Sprite spriteTmp;
        tmp.setColor(sf::Color::Black);
        tmp.setPosition(sf::Vector2f(20,20));
        tmp.setString("At the beginning of each turn, ");
        _pageThreeTexts.push_back(tmp);
        tmp.setPosition(sf::Vector2f(20,40));
        tmp.setString("you will take damage equals to ");
        _pageThreeTexts.push_back(tmp);
        spriteTmp = _game.assets.icons.burnt.createSprite();
        spriteTmp.setPosition(sf::Vector2f(332, 28));
        _pageThreeSprites.push_back(spriteTmp);
        tmp.setPosition(sf::Vector2f(20,60));
        tmp.setString("Afterwhich, it will be decreased by 1");
        _pageThreeTexts.push_back(tmp);

        tmp.setPosition(sf::Vector2f(20,90));
        tmp.setString("You will get a maximum of 6 dice and");
        _pageThreeTexts.push_back(tmp);
        tmp.setPosition(sf::Vector2f(20,110));
        tmp.setString("one less dice for every");
        _pageThreeTexts.push_back(tmp);
        spriteTmp = _game.assets.icons.stunned.createSprite();
        spriteTmp.setPosition(sf::Vector2f(260, 110));
        _pageThreeSprites.push_back(spriteTmp);

        tmp.setPosition(sf::Vector2f(20,160));
        tmp.setString("You can roll all the dice by clicking on ");
        _pageThreeTexts.push_back(tmp);
        tmp.setPosition(sf::Vector2f(20,180));
        tmp.setString("After you roll, you will see the best 7 abilities.");
        _pageThreeTexts.push_back(tmp);
        spriteTmp = _game.assets.gameScreenAssets.rollButton.createSprite();
        spriteTmp.setScale(0.25, 0.25);
        spriteTmp.setPosition(sf::Vector2f(430, 165));
        _pageThreeSprites.push_back(spriteTmp);
        tmp.setString("To use an ability, just click on it");
        tmp.setPosition(sf::Vector2f(20,200));
        _pageThreeTexts.push_back(tmp);
        tmp.setPosition(sf::Vector2f(20,220));
        tmp.setString("If you wish to specify which dice you want to use, you can");
        _pageThreeTexts.push_back(tmp);
        tmp.setPosition(sf::Vector2f(20,240));
        tmp.setString("This is extremely useful if you want to use the          dice");
        _pageThreeTexts.push_back(tmp);
        tmp.setPosition(sf::Vector2f(20,260));
        tmp.setString("instead of the non-frozen ones.");
        _pageThreeTexts.push_back(tmp);
        spriteTmp = _game.assets.icons.frozen.createSprite();
        spriteTmp.setPosition(sf::Vector2f(500, 240));
        _pageThreeSprites.push_back(spriteTmp);
        
        
        tmp.setPosition(sf::Vector2f(20,290));
        tmp.setString("After you use an ability, you can choose to lock     any dice");
        _pageThreeTexts.push_back(tmp);
        tmp.setPosition(sf::Vector2f(20,310));
        tmp.setString("to prevent them from being rerolled");
        _pageThreeTexts.push_back(tmp);
        spriteTmp = _game.assets.gameScreenAssets.lockIcon.createSprite();
        spriteTmp.setPosition(sf::Vector2f(500, 290));
        _pageThreeSprites.push_back(spriteTmp);
        tmp.setPosition(sf::Vector2f(20,330));
        tmp.setString("However, you must reroll at least one die.");
        _pageThreeTexts.push_back(tmp);

        tmp.setPosition(sf::Vector2f(20,380));
        tmp.setString("Alternatively, you can choose to end your turn.");
        _pageThreeTexts.push_back(tmp);
        spriteTmp = _game.assets.gameScreenAssets.doneButton.createSprite();
        spriteTmp.setScale(0.25, 0.25);
        spriteTmp.setPosition(sf::Vector2f(490, 385));
        _pageThreeSprites.push_back(spriteTmp);
    }
}

void HelpScreen::nextPage()
{
    if(_currentPage != 3)
    {
        _currentPage++;
    }
}

void HelpScreen::previousPage()
{
    if(_currentPage != 1)
    {
        _currentPage--;
    }
}
