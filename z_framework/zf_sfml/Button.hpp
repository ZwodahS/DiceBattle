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

/** Button is a simple struct to store 2 sprite, selected / unselected
 *
 */
#ifndef _ZF_SFML_BUTTON_H_
#define _ZF_SFML_BUTTON_H_
#include <SFML/Graphics.hpp>
namespace zf
{
    class Button
    {
    public:
        sf::Sprite selectedSprite;
        sf::Sprite unselectedSprite;
        void setPosition(sf::Vector2f position);
        void updateSelection(sf::Vector2f mousePos);
        Button(const Button &button);
        Button(sf::Sprite selectedSprite, sf::Sprite unselectedSprite, sf::FloatRect size);
        Button();
        ~Button();

        void draw(sf::RenderWindow& window, sf::Time delta);
        const sf::FloatRect &clickBound;
        const bool& selected;

        Button& operator=(const Button &rhs);
    private:
        sf::FloatRect _clickBound;
        bool _selected;
        void setSelected(bool selection);
    };
}
#endif
