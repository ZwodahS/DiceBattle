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
#include "SpriteGroup.hpp"
#include <iostream>
namespace zf
{

    SpriteGroup::SpriteGroup()
        :state(_state), spriteGroups(_spriteGroups), bound(_bound),
        _state(-1), _bound(0,0,0,0)
    {
    }
    
    SpriteGroup::SpriteGroup(const SpriteGroup& copy)
        :state(_state), spriteGroups(_spriteGroups), bound(_bound),
        _state(copy.state), _bound(copy.bound), _spriteGroups(copy.spriteGroups)
    {

    }

    SpriteGroup::SpriteGroup(std::vector<sf::Sprite> g)
        :state(_state), spriteGroups(_spriteGroups), bound(_bound),
        _state(g.size() == 0?-1:0),_spriteGroups(g)
    {
        if(g.size() == 0)
        {
            _bound = sf::FloatRect(0,0,0,0);
        }
        else
        {
            _bound = g[0].getGlobalBounds();
        }
    }
    
    void SpriteGroup::setPosition(sf::Vector2f position)
    {
        for(std::vector<sf::Sprite>::iterator it = _spriteGroups.begin() ; it != _spriteGroups.end() ; ++it)
        {
            (*it).setPosition(position); 
        }
        if(_spriteGroups.size() != 0)
        {
            _bound = _spriteGroups[0].getGlobalBounds();
        }
    }

    void SpriteGroup::setPosition(float x , float y)
    {
        for(std::vector<sf::Sprite>::iterator it = _spriteGroups.begin() ; it != _spriteGroups.end() ; ++it)
        {
            (*it).setPosition(x,y); 
        }
        if(_spriteGroups.size() != 0)
        {
            _bound = _spriteGroups[0].getGlobalBounds();
        }
    }
    
    void SpriteGroup::setState(int s)
    {
        if(s >= _spriteGroups.size() || s < 0)
        {
            // error , do nothing
        }
        else
        {
            _state = s;
        }
    }

    void SpriteGroup::draw(sf::RenderWindow& window, sf::Time delta)
    {
        if(!(state < 0 || state >= _spriteGroups.size()))
        {
            window.draw(_spriteGroups[state]);
        }
    }

    SpriteGroup& SpriteGroup::operator=(const SpriteGroup& rhs)
    {
        this->_state = rhs._state;
        this->_spriteGroups = rhs._spriteGroups;
        this->_bound = rhs._bound;
    }
}
