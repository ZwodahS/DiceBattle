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
#include "Mouse.hpp"
#include "../zf_common/f_inputs.hpp"

zf::Mouse::Mouse()
{
    wheelDelta = 0;
}

zf::Mouse::~Mouse()
{
}

void zf::Mouse::update(sf::Time delta)
{
    update(delta,0);
}

void zf::Mouse::update(sf::Time delta, sf::Int32 wheelDelta)
{
    zf::Input::processKey(left, sf::Mouse::isButtonPressed(sf::Mouse::Left));
    zf::Input::processKey(right, sf::Mouse::isButtonPressed(sf::Mouse::Right));
    zf::Input::processKey(middle, sf::Mouse::isButtonPressed(sf::Mouse::Middle));
}

sf::Vector2i zf::Mouse::getPosition()
{
    return sf::Mouse::getPosition();
}

sf::Vector2i zf::Mouse::getPosition(sf::Window &window)
{
    return sf::Mouse::getPosition(window);
}

sf::Vector2f zf::Mouse::getWorldPosition(sf::RenderWindow &window)
{
    return window.mapPixelToCoords(getPosition(window));
}
