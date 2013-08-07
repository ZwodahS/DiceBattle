#include "GameScreen.hpp"
#include "../Game.hpp"

GameScreen::DieSprite::DieSprite(sf::Int32 i, std::vector<sf::Sprite> f, sf::Sprite d)
    :id(i), faces(f), dieBorder(d), currentFace(DieFace::Sword), random(true), visible(true), randomizerTimer(0),
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
        window.draw(dieBorder);
        window.draw(faces[currentFace]);
    }
}

void GameScreen::DieSprite::setPosition(sf::Vector2f position)
{
    dieBorder.setPosition(position);
    for(std::vector<sf::Sprite>::iterator it = faces.begin() ; it != faces.end() ; ++it)
    {
        (*it).setPosition(position); 
    }
    clickBound.left = position.x;
    clickBound.top = position.y;
}

sf::Vector2f GameScreen::DieSprite::getPosition()
{
    return sf::Vector2f(clickBound.left, clickBound.top);
}

GameScreen::DieSprite GameScreen::makeDie(sf::Int32 id)
{
    std::vector<sf::Sprite> faces;
    faces.push_back(_game.assets.icons.sword.createSprite());
    faces.push_back(_game.assets.icons.shield.createSprite());
    faces.push_back(_game.assets.icons.heal.createSprite());
    faces.push_back(_game.assets.icons.fire.createSprite());
    faces.push_back(_game.assets.icons.ice.createSprite());
    faces.push_back(_game.assets.icons.shock.createSprite());
    return DieSprite(id,faces, _game.assets.icons.die.createSprite());    
}
