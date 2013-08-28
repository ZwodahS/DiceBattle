#include "AbilityScreen.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_common/f_conversion.hpp"
#define ABILITY_PER_PAGE 8
AbilityScreen::AbilityScreen(Game& game, Rules& rule)
    :Screen(game), _currentPage(-1)
    , _nextButton(game.assets.nextButtonSelected.createSprite(), game.assets.nextButton.createSprite(), sf::FloatRect(0,0,25,30))
    , _previousButton(game.assets.previousButtonSelected.createSprite(), game.assets.previousButton.createSprite(), sf::FloatRect(0,0,25,30))
    , _closeButton(game.assets.closeButtonSelected.createSprite(), game.assets.closeButton.createSprite(), sf::FloatRect(0,0,30,30))
{
    setRule(rule);
    _maxPage = 1 + (rule.abilityCount() / ABILITY_PER_PAGE + (rule.abilityCount() % ABILITY_PER_PAGE > 0 ? 1 : 0));
    loadPage(0);
    _nextButton.setPosition(sf::Vector2f(530,440));
    _previousButton.setPosition(sf::Vector2f(500,440));
    _closeButton.setPosition(sf::Vector2f(580,440));
}

AbilityScreen::~AbilityScreen()
{
}

void AbilityScreen::setRule(Rules& rule)
{
    if(&rule == _rules)
    {
        return;
    }
    _rules = &rule;
    // set up all the sprite
}
void AbilityScreen::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    for(std::vector<sf::Sprite>::iterator it = _sprites.begin() ; it != _sprites.end() ; ++it)
    {
        window.draw(*it); 
    }
    for(std::vector<sf::Text>::iterator it = _texts.begin() ; it != _texts.end() ; ++it)
    {
        window.draw(*it); 
    }
    if(_currentPage != _maxPage - 1)
    {
        _nextButton.draw(window, delta);
    }
    if(_currentPage != 0)
    {
        _previousButton.draw(window, delta);
    }
    _closeButton.draw(window, delta);
}
void AbilityScreen::update(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput)
{
    zf::Mouse& mouse = _game.mouse;
    sf::Vector2f mousePos = mouse.getPositionF(window);
    _nextButton.updateSelection(mousePos);
    _previousButton.updateSelection(mousePos);
    _closeButton.updateSelection(mousePos);
    if(handleInput)
    {
        if(mouse.left.thisPressed)
        {
            if(_nextButton.clickBound.contains(mousePos))
            {
                nextPage();
            }
            else if(_previousButton.clickBound.contains(mousePos))
            {
                previousPage();
            }
            else if(_closeButton.clickBound.contains(mousePos))
            {
                _game.toggleShowAbilities(*_rules);
            }
        }
    }
}

void AbilityScreen::textInput(char c)
{
}

void AbilityScreen::loadPage(int page)
{
    if(page == _currentPage || page < 0 || page >= _maxPage)
    {
        // do nothing
        return;
    }
    _sprites.clear();
    _texts.clear();
    _currentPage = page;
    if(_currentPage == 0)
    {
        loadDicePage();
    }
    else
    {
        loadAbilities( (_currentPage - 1) * ABILITY_PER_PAGE, _currentPage * ABILITY_PER_PAGE);
    }
}

void AbilityScreen::loadDicePage()
{
    sf::Sprite sTmp;
    sf::Text tTmp(" ", _game.assets.gameScreenAssets.abilityFont, 18);
    const std::vector<Die>& dice = _rules->getDice();
    int diePos = 0;
    sf::Sprite dieBG = _game.assets.gameScreenAssets.die.createSprite();
    std::string startingHp = "Max hp : " + zf::toString(_rules->getStartingHp());
    tTmp.setString(startingHp);
    tTmp.setPosition(50,10);
    tTmp.setCharacterSize(48);
    _texts.push_back(tTmp);
    tTmp.setCharacterSize(18);
    for(std::vector<Die>::const_iterator it = dice.begin() ; it != dice.end() ; ++it, diePos++)
    {
        // for every die, i need to create 6 die background, and their respective face
        const std::vector<DieFace::eDieFace>& faces = (*it).faces;
        int facePos = 0;
        float bgX = (diePos * 100) + 50;
        std::string s = "Die " + zf::toString(diePos+1);
        tTmp.setString(s);
        tTmp.setPosition(bgX+2, 80);
        _texts.push_back(tTmp);
        for(std::vector<DieFace::eDieFace>::const_iterator it2 = faces.begin() ; it2 != faces.end() ; ++it2, facePos++)
        {
            float bgY = (facePos * 50) + 100;
            dieBG.setPosition(bgX, bgY);
            _sprites.push_back(dieBG);
            sTmp = _game.assets.getSprite((*it2)); 
            sTmp.setPosition(bgX + 8, bgY + 8);
            _sprites.push_back(sTmp);
        }
    }
}

void AbilityScreen::loadAbilities(int start, int end)
{
    const std::vector<Ability>& abilities = _rules->getAbilities();
    for(int abilityPos = 0 , i = start; i < end && i < abilities.size() ; i++ , abilityPos++)
    {
        populateAbility(abilities[i], abilityPos);
    }
}

void AbilityScreen::populateAbility(const Ability ability, int position)
{
    float posY = position * 50 + 20;
    float posX = 70;
    sf::Sprite abilityStrip = _game.assets.gameScreenAssets.abilityStrip.createSprite();
    abilityStrip.setPosition(posX, posY);
    _sprites.push_back(abilityStrip);
    int costPos = 0;
    for(std::vector<DieFace::eDieFace>::const_iterator it = ability.costs.begin() ; it != ability.costs.end() ; ++it, costPos++)
    {
        sf::Sprite s = _game.assets.getSprite(*it);
        s.setPosition(10+ posX + costPos * 30, posY+2);
        _sprites.push_back(s); 
    }
    int effectPos = 0;
    sf::Text tTmp(" ", _game.assets.gameScreenAssets.abilityFont, 18);
    tTmp.setColor(sf::Color::Black);
    for(std::vector<AbilityEffect>::const_iterator it = ability.effects.begin() ; it != ability.effects.end() ; ++it, effectPos++)
    {
        sf::Sprite s = _game.assets.getSprite((*it).type);
        s.setPosition(230 + posX + effectPos*60, posY+2);
        tTmp.setString(zf::toString((*it).value));
        tTmp.setPosition(270 + posX + effectPos*60, posY +2);
        _texts.push_back(tTmp);
        _sprites.push_back(s);
    }
}

void AbilityScreen::nextPage()
{
    if(_currentPage != _maxPage -1)
    {
        loadPage(_currentPage + 1);
    }
}

void AbilityScreen::previousPage()
{
    if(_currentPage != 0)
    {
        loadPage(_currentPage - 1);
    }
}


