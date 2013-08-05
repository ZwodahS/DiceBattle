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
#include "SpriteSheet.hpp"
#include <iostream>
SpriteSheet::SpriteSheet()
    :_managed(false), _currRow(0), _currCol(0), _maxRow(0), _maxCol(0), _texture(0), _bound(0,0,0,0), _spriteSize(0,0,0,0)
{
}

SpriteSheet::SpriteSheet(sf::Texture* texture, sf::IntRect bound)
    :_managed(false), _currRow(0), _currCol(0), _maxRow(0), _maxCol(0), _texture(texture), _bound(bound), _spriteSize(0,0,0,0)
{
}

SpriteSheet::SpriteSheet(sf::Texture* texture, sf::IntRect bound, sf::IntRect spriteSize, int row, int col)
    :_managed(true), _currRow(0), _currCol(0), _maxRow(row), _maxCol(col), _texture(texture), _bound(bound), _spriteSize(spriteSize)
{
}

void SpriteSheet::create(sf::Texture* texture, sf::IntRect bound)
{
    _managed = false;
    _currRow = 0;
    _currCol = 0;
    _maxRow = 0;
    _maxCol = 0;
    _texture = texture;
    _bound = bound;
    _spriteSize = sf::IntRect(0,0,0,0);
}

void SpriteSheet::create(sf::Texture* texture, sf::IntRect bound, sf::IntRect spriteSize, int row, int col)
{
    _managed = true;
    _currRow = 0;
    _currCol = 0;
    _maxRow = row;
    _maxCol = col;
    _texture =texture;
    _bound = bound;
    _spriteSize = spriteSize;
}

TextureRegion SpriteSheet::createRegion(sf::Image image)
{
    if(_managed)
    {
        sf::Vector2u imgSize = image.getSize();
        if(imgSize.x != this->_spriteSize.width || imgSize.y != this->_spriteSize.height)
        {
            return TextureRegion(); 
        }
        sf::IntRect targetBound(_currCol*_spriteSize.width, _currRow*_spriteSize.height, _spriteSize.width, _spriteSize.height);
        TextureRegion returnRegion = internal_createRegion(image,targetBound);
        _currCol++;
        if(_currCol >= _maxCol)
        {
            _currCol = 0;
            _currRow++;
            if(_currRow >= _maxRow)
            {
                _currRow = 0; //just wrap it back. graphics error is better than runtime.
            }
        }
        return returnRegion;
    }
    else
    {
        return createRegion(image,0,0);
    }
}

TextureRegion SpriteSheet::createRegion(sf::Image image, int x , int y)
{
    sf::Vector2u imgSize = image.getSize();
    TextureRegion returnRegion = internal_createRegion(image, sf::IntRect(x,y,imgSize.x,imgSize.y));
    return returnRegion;
}

TextureRegion SpriteSheet::createRegion(sf::IntRect region)
{
    return internal_createRegion(region);
}

SpriteSheet SpriteSheet::createSubSheet(sf::IntRect bound)
{
    bound.top += _bound.top;
    bound.left += _bound.left;
    return SpriteSheet(_texture, bound);
}

SpriteSheet SpriteSheet::createSubSheet(sf::Vector2i position, sf::IntRect spriteSize, int row, int col)
{
    sf::IntRect bound(position.x + _bound.left , position.y + _bound.top, row * spriteSize.width , col * spriteSize.height);
    return SpriteSheet(_texture, bound,spriteSize,row,col);
}

TextureRegion SpriteSheet::internal_createRegion(sf::Image image, sf::IntRect region)
{
    if(_texture == 0)
    {
        return TextureRegion();
    }
    region.top += _bound.top;
    region.left += _bound.left;
    _texture->update(image,region.left,region.top);
    return TextureRegion(_texture, region);
}

TextureRegion SpriteSheet::internal_createRegion(sf::IntRect region)
{
    if(_texture == 0)
    {
        return TextureRegion();
    }
    region.top += _bound.top;
    region.left += _bound.left;
    return TextureRegion(_texture, region);
}
