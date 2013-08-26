#include "GameScreen.hpp"
#include "../Game.hpp"
#include "../../z_framework/zf_sfml/f_common.hpp"
GameScreen::DieSprite::DieSprite(Die di, std::vector<sf::Sprite> f, sf::Sprite d, sf::Sprite sb, sf::Sprite lock)
    :die(di), faces(f), dieBorder(d), selectionBorder(sb), currentFaceId(0), random(true), lockIcon(lock)
    ,visible(true), randomizerTimer(0), selected(false), locked(false)
    ,clickBound(0,0,DiceSize,DiceSize)
{
    setDie(di);
}

void GameScreen::DieSprite::setRandom(bool r)
{
    this->random = r;
    if(!random)
    {
        randomizerTimer = 0 ;
    }
}

void GameScreen::DieSprite::setVisible(bool v)
{
    this->visible = v;
}


void GameScreen::DieSprite::toggleLocked()
{
    this->locked = !this->locked;
}

void GameScreen::DieSprite::toggleSelection()
{
    this->selected = !this->selected;
}

void GameScreen::DieSprite::setDie(Die& d)
{
    this->die = d;
    if(die.frozen)
    {
        this->dieBorder.setColor(sf::Color(160,230,230,255));
    }
    else
    {
        this->dieBorder.setColor(sf::Color(255,255,255,255));
    }

}

void GameScreen::DieSprite::update(sf::RenderWindow& window, const sf::Time& delta)
{
}

void GameScreen::DieSprite::draw(sf::RenderWindow& window, const sf::Time& delta)
{
    if(random)
    {
        randomizerTimer+=delta.asSeconds();
        if(randomizerTimer >= GameScreen::RandomizerChangeRate)
        {
            currentFaceId = rand() % faces.size();
            randomizerTimer -= GameScreen::RandomizerChangeRate;
        }
    }
    if(visible)
    {
        if(selected)
        {
            window.draw(selectionBorder);
        }
        window.draw(dieBorder);
        if(die.rolled)
        {
            if(random)
            {
                window.draw(faces[currentFaceId]);
            }
            else
            {
                window.draw(faces[die.currentFaceId]);
            }
        }
        if(locked)
        {
            window.draw(lockIcon);
        }
    }
}

void GameScreen::DieSprite::setAlpha(float alpha)
{
    zf::setAlpha(selectionBorder, alpha);
    zf::setAlpha(dieBorder, alpha);
    for(std::vector<sf::Sprite>::iterator it = faces.begin() ; it != faces.end() ; ++it)
    {
        zf::setAlpha((*it), alpha); 
    }
}

void GameScreen::DieSprite::setPosition(sf::Vector2f position)
{
    dieBorder.setPosition(position);
    selectionBorder.setPosition(position);
    for(std::vector<sf::Sprite>::iterator it = faces.begin() ; it != faces.end() ; ++it)
    {
        (*it).setPosition(position + sf::Vector2f(7,7)); 
    }
    clickBound.left = position.x;
    clickBound.top = position.y;
    lockIcon.setPosition(position + sf::Vector2f(30,30));
}

sf::Vector2f GameScreen::DieSprite::getPosition()
{
    return sf::Vector2f(clickBound.left, clickBound.top);
}

void GameScreen::DieSprite::move(sf::Vector2f move)
{
    sf::Vector2f curr = getPosition();
    setPosition(curr + move);
}

GameScreen::DieSprite GameScreen::makeDie(Die& die)
{
    std::vector<sf::Sprite> faces;
    for(std::vector<DieFace::eDieFace>::iterator it = die.faces.begin() ; it != die.faces.end() ; ++it)
    {
        faces.push_back(_game.assets.getSprite(*it));
    }
    DieSprite d(die,faces, _game.assets.gameScreenAssets.die.createSprite(), _game.assets.gameScreenAssets.dieSelectionBorder.createSprite(), _game.assets.gameScreenAssets.lockIcon.createSprite());
    return d;
}
