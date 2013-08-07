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
#include "ColorShiftInstruction.hpp"
#include "AnimationObject.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

ColorShiftInstruction::ColorShiftInstruction(sf::Color& startingColor, sf::Color& endingColor, float time)
    :_red(startingColor.r), _green(startingColor.g), _blue(startingColor.b), _alpha(startingColor.a),
    _changeRed((endingColor.r - startingColor.r) / time), _changeGreen((endingColor.g - startingColor.g) / time), _changeBlue((endingColor.b - startingColor.b)/time),
    _changeAlpha((endingColor.a - startingColor.a) / time),
    _startingColor(startingColor), _endingColor(endingColor), _done(false), _time(0), _totalTime(time)
{
}


bool ColorShiftInstruction::update(sf::RenderWindow* window, sf::Time delta, AnimationObject* object)
{
    if(!_done)
    {
        if(_time >= _totalTime)
        {
            _done = true;
            object->setColor(_endingColor);
        }
        else
        {
            float deltaFloat = delta.asSeconds();
            _red += _changeRed * deltaFloat;
            _blue += _changeBlue * deltaFloat;
            _green += _changeGreen * deltaFloat;
            _alpha += _changeAlpha * deltaFloat;

            object->setColor(sf::Color(_red,_green,_blue,_alpha));
            _time += delta.asSeconds();
        }
    }
    return isDone(object);
}

bool ColorShiftInstruction::isDone(AnimationObject* object)
{
    return _done;
}
