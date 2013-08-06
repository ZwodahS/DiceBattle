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
#ifndef _ZF_SFML_MOUSE_H_
#define _ZF_SFML_MOUSE_H_

#include "../zf_common/InputState.hpp"

#include <SFML/Graphics.hpp>
namespace zf
{
    // There is no need to keep track of the position , since you can get it directly.
    class Mouse
    {
        public:
            InputState left;
            InputState right;
            InputState middle;
            sf::Int32 wheelDelta;
            void update(sf::Time delta);
            void update(sf::Time delta, sf::Int32 wheelDelta);
            sf::Vector2i getPosition();
            sf::Vector2i getPosition(sf::Window &window);
            sf::Vector2f getWorldPosition(sf::RenderWindow &window);
            Mouse();
            ~Mouse();
    };
}
#endif
