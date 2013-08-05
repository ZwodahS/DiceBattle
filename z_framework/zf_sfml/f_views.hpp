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
#ifndef _ZF_SFML_FUNCTIONS_VIEWS_H_
#define _ZF_SFML_FUNCTIONS_VIEWS_H_
#include <SFML/Graphics.hpp>
#include <vector>

namespace zf
{
    class View
    {
        public:
            static sf::Vector2f topLeft(sf::View view)
            {
                sf::Vector2f center = view.getCenter();
                sf::Vector2f size = view.getSize();
                return sf::Vector2f(center - (size/2.0f));
            };
            static sf::Vector2f bottomRight(sf::View view)
            {
                sf::Vector2f center = view.getCenter();
                sf::Vector2f size = view.getSize();
                return sf::Vector2f(center + (size/2.0f));
            };
            // return the start row / col and the number of tiles in this view.
            static sf::IntRect viewToTileBounds(sf::View view, int rowSize, int colSize, int maxRow, int maxCol)
            {
                sf::Vector2f topLeft = zf::View::topLeft(view);
                sf::Vector2f bottomRight = zf::View::bottomRight(view);
                sf::IntRect rect = sf::IntRect(0,0,0,0);
                rect.left = (int)(topLeft.x / colSize);
                rect.top = (int)(topLeft.y / rowSize);
                rect.width = (int)(bottomRight.x / colSize);
                rect.height = (int)(bottomRight.y / rowSize);
                rect.left = rect.left <= 0 ? 0 : rect.left - 1;
                rect.top = rect.top <= 0 ? 0 : rect.top - 1;
                rect.width = rect.width >= maxCol ? maxCol : rect.width + 1;
                rect.height = rect.height >= maxRow ? maxRow : rect.height + 1;
                return rect;
            }
    };
}
#endif
