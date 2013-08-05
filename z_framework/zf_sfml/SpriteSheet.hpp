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
#ifndef _ZF_SFML_SPRITESHEET_H_
#define _ZF_SFML_SPRITESHEET_H_
#include "TextureRegion.hpp"
#include <SFML/Graphics.hpp>

class SpriteSheet
{
    public:
        SpriteSheet(); // empty spritesheet.
        /**
         * Create a spritesheet with this texture. the bound define the region that can be used.
         * There is no bound checking. Just make sure you know what you are doing.
         */
        SpriteSheet(sf::Texture* texture, sf::IntRect bound);
        void create(sf::Texture* texture, sf::IntRect bound);
        SpriteSheet(sf::Texture* texture, sf::IntRect bound, sf::IntRect spriteSize, int row, int col);
        void create(sf::Texture* texture, sf::IntRect bound, sf::IntRect spriteSize, int row, int col);

        /**
         * Create region at the current position. If this spritesheet is managed, then it will be slot at the correct position.
         * If the spritesheet is not managed, then it will be the same as createRegion(image,0,0);
         */
        TextureRegion createRegion(sf::Image image);
        
        TextureRegion createRegion(sf::Image image, int x , int y);
        TextureRegion createRegion(sf::IntRect region);
        // Note that the region that the sprite is created is always relative to the origin bound that is specified.
        // i.e. if this sprite sheet is created with bound = (100,100,500,500),
        // then when createRegion(image) is called, the image will be added to sf::Vector2i(100,100) and the region that is returned will be at (100,100,w,h) where w = width of image, and h = height of image.
        //
        SpriteSheet createSubSheet(sf::IntRect bound);
        SpriteSheet createSubSheet(sf::Vector2i position , sf::IntRect spriteSize, int row , int col);
    private:     
        sf::Texture* _texture;
        sf::IntRect _bound;

        // for managed spriteSheet. Managed SpriteSheet means that the size in that spritesheet is the same and when createRegion is called, it will be added to the correct slot
        // and the correct region will be returned.
        bool _managed;
        sf::IntRect _spriteSize;
        int _currRow;
        int _currCol;
        int _maxRow;
        int _maxCol;
        
        TextureRegion internal_createRegion(sf::Image, sf::IntRect region);
        TextureRegion internal_createRegion(sf::IntRect region);
};

#endif
