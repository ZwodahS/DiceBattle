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
#include "AnimationObject.hpp"
#include "AnimationInstruction.hpp"
AnimationObject::AnimationObject()
    :_done(0)
{
    this->_instruction = 0;
}

AnimationObject::~AnimationObject()
{
    if(_instruction != 0)
    {
        delete _instruction;
    }
}

bool AnimationObject::update(sf::RenderWindow& window, sf::Time delta)
{
    if(done())
    {
        return true;
    }
    bool doneness = _instruction->update(window,delta,*this);
    if(_done != 0)
    {
        *_done = doneness;
    }
    return doneness;
}

void AnimationObject::setInstruction(AnimationInstruction* instruction)
{
    if(_instruction != 0)
    {
        delete _instruction;
    }
    this->_instruction = instruction;
    if(_done != 0)
    {
        *_done = done();
    }
}

void AnimationObject::setDoneVariable(bool* d)
{
    this->_done = d;
}
bool AnimationObject::done()
{
    return _instruction == 0 ? true : _instruction->isDone(*this);
}
