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
#ifndef _ZF_SFML_ANIMATIONS_MOVEINSTRUCTION_H_
#define _ZF_SFML_ANIMATIONS_MOVEINSTRUCTION_H_
#include "AnimationInstruction.hpp"
class MoveInstruction : public AnimationInstruction
{
    public:
        MoveInstruction(sf::Vector2f moveVector, float moveSecs);
        MoveInstruction(const MoveInstruction &mi);
        ~MoveInstruction();

        bool update(sf::RenderWindow* window, sf::Time delta, AnimationObject* object);
        bool isDone(AnimationObject* object);

    private:
        sf::Vector2f _moveVector;
        float _timeMax;
        float _timeCurrent;

        bool _done;

};
#endif
