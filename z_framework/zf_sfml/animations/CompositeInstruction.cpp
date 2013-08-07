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
#include "CompositeInstruction.hpp"
#include "AnimationObject.hpp"
CompositeInstruction::CompositeInstruction(bool ordered)
{
    this->_instructions = std::vector<AnimationInstruction*>(0);
    this->_done = false;
    this->_ordered = ordered;
    this->currIn = 0;
}

CompositeInstruction::~CompositeInstruction()
{
    for(int i = 0 ; i < _instructions.size() ; i++)
    {
        delete _instructions[i]; 
    }
}

CompositeInstruction* CompositeInstruction::addInstruction(FadeInstruction fi)
{
    FadeInstruction* f = new FadeInstruction(fi);
    this->_instructions.push_back(f);
    return this;
}

CompositeInstruction* CompositeInstruction::addInstruction(MoveToInstruction mi)
{
    MoveToInstruction* m = new MoveToInstruction(mi);
    this->_instructions.push_back(m);
    return this;
}

bool CompositeInstruction::update(sf::RenderWindow* window, sf::Time delta, AnimationObject* object)
{
    if(!_done)
    {
        if(!_ordered)
        {
            _done = true;
            for(int i = 0 ; i < _instructions.size() ; i++)
            {
                if(!_instructions[i]->isDone(object) && !_instructions[i]->update(window,delta,object))
                {
                    _done = false;
                }
            }
        }
        else
        {
            if(currIn == _instructions.size())
            {
                _done = true; // just in case
            }
            else
            {
                if(!_instructions[currIn]->isDone(object))
                {
                    if(_instructions[currIn]->update(window,delta,object))
                    {
                        currIn++;
                    }
                }
                else
                {
                    currIn ++; // shouldn't even get here.
                }
            }
        }
    }
    return _done;
}

bool CompositeInstruction::isDone(AnimationObject* object)
{
    return _done;
}

CompositeInstruction* CompositeInstruction::fade(int startingAlpha, int endingAlpha, float time)
{
    FadeInstruction* fi = new FadeInstruction(startingAlpha, endingAlpha, time);
    this->_instructions.push_back(fi);
    return this;
}

CompositeInstruction* CompositeInstruction::moveTo(sf::Vector2f source, sf::Vector2f target, float delta)
{
    MoveToInstruction* mi = new MoveToInstruction(source,target,delta);
    this->_instructions.push_back(mi);
    return this;
}

CompositeInstruction* CompositeInstruction::move(sf::Vector2f moveVec, float duration)
{
    MoveInstruction* mi = new MoveInstruction(moveVec,duration);
    this->_instructions.push_back(mi);
    return this;
}

CompositeInstruction* CompositeInstruction::wait(float waitTime)
{
    this->_instructions.push_back(new WaitInstruction(waitTime));
    return this;
}
