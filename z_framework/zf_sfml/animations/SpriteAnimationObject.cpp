/*
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *                   Version 2, December 2004
 * 
 * Copyright (C) 2013 ZwodahS(ericnjf@gmail.com) 
 * zwodahs.wordpress.com
 * 
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 * 
 *           DO WHAT THE **** YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 
 *  0. You just DO WHAT THE **** YOU WANT TO.
 * 
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details. 
 */
#include "SpriteAnimationObject.hpp"
SpriteAnimationObject::SpriteAnimationObject(sf::Sprite sprite)
    :_sprite(sprite)
{
}

SpriteAnimationObject::~SpriteAnimationObject()
{
}

void SpriteAnimationObject::setAlpha(float alpha)
{
    sf::Color color = this->_sprite.getColor();
    color.a = alpha;
    this->_sprite.setColor(color);
}

void SpriteAnimationObject::setPosition(sf::Vector2f position)
{
    this->_sprite.setPosition(position);
}

void SpriteAnimationObject::movePosition(sf::Vector2f moves)
{
    sf::Vector2f position = this->_sprite.getPosition();
    this->_sprite.setPosition(position + moves);
}

void SpriteAnimationObject::draw(sf::RenderWindow& window, sf::Time delta)
{
    window.draw(this->_sprite);
}

void SpriteAnimationObject::setColor(sf::Color color)
{
    this->_sprite.setColor(color);
}
