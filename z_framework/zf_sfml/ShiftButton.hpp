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
/**
 * ShiftButton is a type of button that shift its position if it is hovered. 
 */
#ifndef _ZF_SFML_SHIFTBUTTON_H_
#define _ZF_SFML_SHIFTBUTTON_H_
#include "f_common.hpp"
#include "animations/iAnimatable.hpp"
#include <SFML/Graphics.hpp>
namespace zf
{
    class ShiftButton : public iAnimatable
    {
    public:
        ShiftButton(sf::Sprite buttonSprite, sf::Vector2f shiftMax, float shiftDuration);
        ShiftButton(const ShiftButton& shiftButton);
        ShiftButton();
        ~ShiftButton();

        void setPosition(sf::Vector2f position);
        void updateSelection(const sf::Vector2f& mousePos, const sf::Time& delta);

        void draw(sf::RenderWindow& window, const sf::Time& delta);
        
        const sf::FloatRect& bound;

        ShiftButton& operator= (const ShiftButton& rhs);
        /// iAnimatable ///
        void setAlpha(float alpha);
        void move(sf::Vector2f move);
        void setColor(sf::Color color);
        sf::Vector2f getPosition();
    private:

        sf::Sprite _sprite;
        sf::Vector2f _actualPosition;
        sf::Vector2f _currentPosition;
        sf::Vector2f _shiftMax;
        sf::FloatRect _bound;

        sf::Vector2f _currentShift;
        float _shiftDuration;
        void updateShift();
    };
}
#endif
