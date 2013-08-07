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
#include "AnimatableObject.hpp"
AnimatableObject::AnimatableObject(iAnimatable& a)
    :_animatable(a), _isPtr(false)
{
}

AnimatableObject::AnimatableObject(iAnimatable* a)
    :_animatable(*a), _isPtr(true)
{
}

AnimatableObject::~AnimatableObject()
{
    if(_isPtr)
    {
        delete &_animatable;
    }
}

void AnimatableObject::setAlpha(float alpha)
{
    _animatable.setAlpha(alpha);
}

void AnimatableObject::setPosition(sf::Vector2f position)
{
    _animatable.setPosition(position);
}

void AnimatableObject::setColor(sf::Color color)
{
    _animatable.setColor(color);
}

void AnimatableObject::movePosition(sf::Vector2f move)
{
    _animatable.move(move);
}

void AnimatableObject::draw(sf::RenderWindow* window , sf::Time delta)
{
    if(_isPtr)
    {
        _animatable.draw(*window, delta); 
    }
}
