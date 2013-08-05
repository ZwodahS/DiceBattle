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
#include "MoveToInstruction.hpp"
#include "AnimationObject.hpp"
MoveToInstruction::MoveToInstruction(sf::Vector2f source, sf::Vector2f target, float delta)
{
    this->_done = false;
    this->_position = source;
    this->_target = target;
    this->_move = (_target - _position) / delta;
}
MoveToInstruction::MoveToInstruction(const MoveToInstruction &mi)
{
    this->_done = false;
    this->_position = mi._position;
    this->_move = mi._move;
    this->_target = mi._target;
}

MoveToInstruction::~MoveToInstruction()
{
}

bool MoveToInstruction::update(sf::RenderWindow* window, sf::Time delta, AnimationObject* object)
{
    if(!_done)
    {
        this->_position += _move * delta.asSeconds();
        if(overShootDestination())
        {
            _done = true;
        }
        object->setPosition(_position);
    }
    return _done;
}

bool MoveToInstruction::isDone(AnimationObject* object)
{
    return _done;
}

bool MoveToInstruction::overShootDestination()
{
    bool x_done = false;
    bool y_done = false;
    if(_move.x > 0)
    {
        if(_position.x > _target.x)
        {
            x_done = true;
            _position.x = _target.x;
        }
    }
    else if(_move.x < 0)
    {
        if(_position.x < _target.x)
        {
            x_done = true;
            _position.x = _target.x;
        }
    }
    else
    {
        x_done =true;
    }


    if(_move.y > 0)
    {
        if(_position.y > _target.y)
        {
            y_done = true;
            _position.y = _target.y;
        }
    }
    else if(_move.y < 0)
    {
        if(_position.y < _target.y)
        {
            y_done = true;
            _position.y = _target.y;
        }
    }
    else
    {
        x_done =true;
    }
    return x_done && y_done;
}
