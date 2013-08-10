#include "GameScreen.hpp"
#include "../Game.hpp"

GameScreen::DieSprite::DieSprite(sf::Int32 i, std::vector<sf::Sprite> f, sf::Sprite d, sf::Sprite sb)
    :id(i), faces(f), dieBorder(d), selectionBorder(sb), currentFace(DieFace::Sword), actualFace(DieFace::Sword), random(true), empty(true)
    ,visible(true), frozen(false), randomizerTimer(0), 
    clickBound(0,0,DiceSize,DiceSize)
{
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

void GameScreen::DieSprite::setEmpty(bool e)
{
    this->empty = e;
}

void GameScreen::DieSprite::toggleSelection()
{
    this->selected = !this->selected;
}
void GameScreen::DieSprite::setFrozen(bool f)
{
    this->frozen = f;
    if(frozen)
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
            currentFace = DieFace::randomFace(currentFace);
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
        if(!this->empty)
        {
            if(random)
            {
                window.draw(faces[currentFace]);
            }
            else
            {
                window.draw(faces[actualFace]);
            }
        }
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
}

sf::Vector2f GameScreen::DieSprite::getPosition()
{
    return sf::Vector2f(clickBound.left, clickBound.top);
}

GameScreen::DieSprite GameScreen::makeDie(Die& die)
{
    std::vector<sf::Sprite> faces;
    for(std::vector<DieFace::eDieFace>::iterator it = die.faces.begin() ; it != die.faces.end() ; ++it)
    {
        faces.push_back(_game.assets.getSprite(*it));
    }
    DieSprite d = DieSprite(die.id,faces, _game.assets.gameScreenAssets.die.createSprite(), _game.assets.gameScreenAssets.dieSelectionBorder.createSprite());    
    d.setFrozen(die.frozen);
    d.setEmpty(!die.rolled);
    return d;
}
