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
#ifndef _ZF_COMMON_GRID_H_
#define _ZF_COMMON_GRID_H_
/*
 * Stores the position in a Grid place system (row by column)
 */
#include <math.h>
struct Grid
{
    int row;
    int col;
    Grid();
    Grid(int row, int col);
    ~Grid();

    /* 
     * Converts a position value to a grid value.
     * The float value is cast to the int value using floor.
     */ 
    static Grid toGrid(float x, float y, int gridSize, int gridSpacing)
    {
        // This is extremely problematic at the moment, because this converts from a continuous value to a discrete value.
        // Currently it is converted using floor, but I may want to use ceil sometimes.
        // If the situation requires, add a boolean to determine if floor/ceil is used.
        Grid g;
        g.col = floor(x) / (gridSize + gridSpacing);
        g.row = floor(y) / (gridSize + gridSpacing);
        return g;
    }
    // operator overloaded.
    Grid& operator+=(const Grid &rhs);
    Grid& operator-=(const Grid &rhs);
    
};
// operator overloaded.
bool operator==(const Grid &lhs, const Grid &rhs);
bool operator!=(const Grid &lhs, const Grid &rhs);
Grid operator-(Grid lhs, const Grid& rhs);
Grid operator+(Grid lhs, const Grid& rhs);

#endif
