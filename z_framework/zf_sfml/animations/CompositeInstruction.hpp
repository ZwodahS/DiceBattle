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
#ifndef _ZF_SFML_ANIMATIONS_COMPOSITEINSTRUCTION_H_
#define _ZF_SFML_ANIMATIONS_COMPOSITEINSTRUCTION_H_
#include "AnimationInstruction.hpp"
#include "FadeInstruction.hpp"
#include "MoveToInstruction.hpp"
#include "MoveInstruction.hpp"
#include "WaitInstruction.hpp"
#include <vector>
class AnimationObject;
class CompositeInstruction : public AnimationInstruction
{
    public:
        // if ordered is true , then the instruction is executed one after another.
        // if not ordered , the instruction is executed all at the same time.
        CompositeInstruction(bool ordered = false);
        ~CompositeInstruction();
        bool update(sf::RenderWindow& window, sf::Time delta,AnimationObject& object);
        bool isDone(AnimationObject& object);
        
        // all functions here return the pointer to itself to allow for chaining.
        // add a fade instruction , copying the information from another fade instruction.
        CompositeInstruction* addInstruction(FadeInstruction fi);
        // add a fade instruction using parameters.
        CompositeInstruction* fade(int startingAlpha, int endingAlpha, float time);
        // add a move to instruction, copying the information  from another move to instruction
        CompositeInstruction* addInstruction(MoveToInstruction mi);

        CompositeInstruction* moveTo(sf::Vector2f source, sf::Vector2f target, float delta);
        CompositeInstruction* move(sf::Vector2f moveVec, float duration);

        CompositeInstruction* wait(float waitTime);
    private:
        std::vector<AnimationInstruction*> _instructions;
        bool _ordered;
        bool _done;
        int currIn;
};

#endif
