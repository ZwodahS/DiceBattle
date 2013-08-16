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

#ifndef _ZF_SFML_SPRITEGROUP_H_
#define _ZF_SFML_SPRITEGROUP_H_
#include "animations/iAnimatable.hpp"
#include <SFML/Graphics.hpp>
/** 
 * SpriteGroup is used to group sprites state together. This allow group manipulation of sprite and only draw the
 * state that ie needed.
 *
 * SpriteGroup assumed that the size of the sprites are the same.
 */
#include <vector>
namespace zf
{
    class SpriteGroup : public iAnimatable
    {
    public:
        const std::vector<sf::Sprite>& spriteGroups;
        const int &state;
        const sf::FloatRect &bound;
        /**
         * Set the position for the group.
         */
        void setPosition(sf::Vector2f position);
        void setPosition(float x , float y);
        
        SpriteGroup(); // empty sprite group
        SpriteGroup(const SpriteGroup& copy);
        SpriteGroup(std::vector<sf::Sprite> g);  // the size of the bound is assumed to be the global bound of the first sprite or 0,0,0,0 if the list is empty
        
        void setState(int state);
        SpriteGroup& operator=(const SpriteGroup &rhs);
        
        /**
         * Draw the current sprite group. This will draw the sprite for the current state.
         */
        void draw(sf::RenderWindow& window, sf::Time delta);
        void setAlpha(float alpha);
        void move(sf::Vector2f moveVec);
        void setColor(sf::Color color);
        sf::Vector2f getPosition();
    private:
        int _state;
        std::vector<sf::Sprite> _spriteGroups;
        sf::FloatRect _bound;
    };
};

#endif
