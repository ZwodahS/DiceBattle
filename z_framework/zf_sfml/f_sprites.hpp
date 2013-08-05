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
#ifndef _ZF_SFML_FUNCTIONS_SPRITES_H_
#define _ZF_SFML_FUNCTIONS_SPRITES_H_
#include <SFML/Graphics.hpp>
#include <vector>
namespace zf
{
    class Sprite
    {
        public:
            static std::vector<sf::Sprite> split4(sf::Sprite sprite)
            {
                std::vector<sf::Sprite> splits = std::vector<sf::Sprite>(0);
                const sf::Texture* texture = sprite.getTexture();
                sf::IntRect baseRect = sprite.getTextureRect();
                sf::Vector2f position = sprite.getPosition();
                splits.push_back(sf::Sprite(*texture, sf::IntRect(baseRect.left,baseRect.top,baseRect.width/2,baseRect.height/2)));
                splits[0].setPosition(position.x,position.y);
                splits[0].setColor(sprite.getColor());
                splits.push_back(sf::Sprite(*texture, sf::IntRect(baseRect.left+(baseRect.width/2), baseRect.top, baseRect.width/2, baseRect.height/2)));
                splits[1].setPosition(position.x+baseRect.width/2,position.y);
                splits[1].setColor(sprite.getColor());
                splits.push_back(sf::Sprite(*texture, sf::IntRect(baseRect.left, baseRect.top+(baseRect.height/2), baseRect.width/2 , baseRect.height/2)));
                splits[2].setPosition(position.x,position.y+baseRect.height/2);
                splits[2].setColor(sprite.getColor());
                splits.push_back(sf::Sprite(*texture, sf::IntRect(baseRect.left+(baseRect.width/2), baseRect.top+(baseRect.height/2), baseRect.width/2 , baseRect.height/2)));
                splits[3].setPosition(position.x+baseRect.width/2,position.y+baseRect.height/2);
                splits[3].setColor(sprite.getColor());
                return splits;
            }

    };
}
#endif
