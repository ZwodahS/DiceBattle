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


/* 
 * Define a template 2D space to store grid based objects.
 */
#ifndef _ZF_COMMON_TWODSPACE_H_
#define _ZF_COMMON_TWODSPACE_H_
#include "Grid.hpp"
#include <vector>
template <class T>
class TwoDSpace
{
public:
    /*
     * An iterator for the space.
     * Do not create the iterator. Use the 2D space to iterates.
     */
    class Iterator
    {
    public:
        Iterator()
            :current(_current)
        {
            _current = Grid(-1,-1);
            _space = 0;
        }
        /**
         * Start inclusive
         * End inclusive
         */
        Iterator(Grid start, Grid end, TwoDSpace* space, bool iteratorType)
            :current(_current)
        {
            this->_current = start;
            this->_start = start;
            this->_end = end;
            this->_space = space;
            this->_type = iteratorType;
        }
        ~Iterator()
        {

        }
        
        /**
         * Get the current value at the iterator
         */
        T get()
        {
            return _space->get(_current);
        };

        /**
         * Set the current value at the iterator and return the old value
         */
        T set(T value)
        {
            return _space->set(_current, value);
        };

        /**
         * Set this value to empty(the default value specified during space construction) and return the old value
         */
        T empty()
        {
            return _space->empty(_current);
        }
        /**
         * Check if the iterator has ended.
         */
        bool end()
        {
            return _current == Grid(-1,-1);
        }
        /**
         * Iterate to the next object.
         */ 
        Iterator& operator++()
        {
            return next();
        };
        /**
         * Iterate to the next object, same as operator++
         */
        Iterator& next()
        {
            if(!end())
            {
                if(_type)
                {
                    if(_start.col <= _end.col)
                    {
                        _current.col++;
                        if(_current.col >= _end.col)
                        {
                            _current.col = _start.col;
                            _current.row += _start.row <= _end.row ? 1 : -1;
                            if(_current.row == _end.row)
                            {
                                // end.
                                _current = Grid(-1,-1);
                            }
                        }
                    }
                    else
                    {
                        _current.col--;
                       if(_current.col <= _end.col)
                       {
                            _current.col = _start.col;
                            _current.row += _start.row <= _end.row ? 1 : -1;
                            if(_current.row == _end.row)
                            {
                                _current = Grid(-1,-1);
                            }
                       } 
                    }
                }
                else
                {
                    if(_start.row <= _end.row)
                    {
                        _current.row++;
                        if(_current.row >= _end.row)
                        {
                            _current.row = _start.row;
                            _current.col += _start.col <= _end.col ? 1 : -1 ;
                            if(_current.col == _end.col)
                            {
                                _current = Grid(-1,-1);
                            }
                        }
                    }
                    else
                    {
                        _current.row--;
                        if(_current.row <= _end.row)
                        {
                            _current.row = _start.row;
                            _current.col += _start.col <= _end.col ? 1 : -1 ;
                            if(_current.col == _end.col)
                            {
                                _current = Grid(-1,-1);
                            }
                        }
                    }
                }
            }
            return *this;
        };
        const Grid &current;
    protected:
        Grid _current;
        Grid _start;
        Grid _end;
        TwoDSpace* _space; 
        bool _type; // true = row iterator (col++ first) , false = col iterator
    };
    /**
     * creates a empty 2D space
     */
    TwoDSpace()
        :row(_row) , col(_col)
    {
        _2dspace = std::vector<std::vector<T> >(0,std::vector<T>(0));
        this->_row = 0;
        this->_col = 0;
    }
    /** 
     * Create a 2D space of a specific size and fill it with default value
     */
    TwoDSpace(int row, int col, T defaultValue)
        :row(_row), col(_col)
    {
        init(row, col, defaultValue);
    }
    /**
     * Copy a Two space.
     */
    TwoDSpace(const TwoDSpace& copy)
        :row(_row), col(_col), 
        _row(copy._row), _col(copy._col), 
        _2dspace(copy._2dspace)
    {
    }

    /**
     * Get the value at row col. 
     * If the row/col is in range, return value.
     * if out of range, return the default value.
     */
    T get(int row, int col)
    {
        if(inRange(row,col))
        {
            return _2dspace[row][col];
        }
        else
        {
            return _defaultValue;
        }
    };
    /**
     * Get the value at a grid.
     * same as get(grid.row, grid.col);
     */
    T get(Grid grid)
    {
        return get(grid.row,grid.col);
    }
    /**
     * Set the value at row col, and return the old value.
     * If the row/col is in range, the old value is returned.
     * If the row/col is out of range, nothing is changed and the default value is returend.
     */ 
    T set(int row, int col, T value)
    {
        if(!inRange(row,col))
        {
            return _defaultValue;
        }
        else
        {
            T v = _2dspace[row][col];
            _2dspace[row][col] = value;
            return v;
        }
    }
    /**
     * Set the value at row and col
     * same as set(grid.row, grid.col, value)
     */
    T set(Grid grid, T value)
    {
        return set(grid.row, grid.col, value);
    }
    /*
     * set the value at row col to default value. return the old value at the position.
     */
    T empty(int row, int col)
    {
        return set(row,col,_defaultValue);
    }
    /**
     * set the value at grid. return the old value at the position.
     */
    T empty(Grid grid)
    {
        return empty(grid.row, grid.col);
    }
    /*
     * Return a sub space, topleft and bottom right inclusive.
     * if any of the space is out of range, they will be filled with default value instead.
     * the minimum space is 1/1
     * POTENTIAL BUG : DO NOT USE NEGATIVE VALUE.
     */
    TwoDSpace<T> subspace(Grid topLeft, Grid bottomRight)
    {
        TwoDSpace<T> collision = TwoDSpace<T>(bottomRight.row - topLeft.row  + 1 , bottomRight.col - topLeft.col + 1 , _defaultValue);
        for(int r = topLeft.row, rr = 0 ; r <= bottomRight.row ; r++ , rr++)
        {
            for(int c = topLeft.col, cc = 0 ; c <= bottomRight.col ; c++ , cc++)
            {
                if(inRange(r,c))
                {
                    collision.set(rr,cc,get(r,c));
                }
            }
        }
        return collision;
    }
    /**
     * check if the row and col is in range.
     */
    bool inRange(int row, int col)
    {
        if(row < 0 || row >= _2dspace.size() || col < 0 || col >= _2dspace[row].size())
        {
            return false;
        }
        return true;
    }
    /**
     * check if the row and col is in range.
     */
    bool inRange(Grid grid)
    {
        return inRange(grid.row, grid.col);
    }
    /**
     * Iterates the entire 2D space, Col first then row.
     * if reversed Row is true, the row will start from the last row and iterates to the first row.
     * if reversed Col is true, the col will start from the last col and iterates to the first col.
     */
    Iterator iteratesColRow(bool reversedRow = false , bool reversedCol = false) // col ++ follow by row ++
    {
        Grid start = Grid(0,0);
        Grid end = Grid(_row,_col);
        if(reversedRow)
        {
            start.row = _row-1;
            end.row = -1;
        }
        if(reversedCol)
        {
            start.col = _col-1;
            end.col = -1;
        }
        return Iterator(start,end, this, true);
    }
    /**
     * Iterates a subspace of the 2D space col follow by row
     * The direction of iteration is will depend on the start end grid.
     */
    Iterator iteratesColRow(Grid start, Grid end)
    {
        return Iterator(start, end, this, true);
    }
    /**
     * Iterates the entire 2D space, Row first then col.
     * if reversed Row is true, the row will start from the last row and iterates to the first row.
     * if reversed Col is true, the col will start from the last col and iterates to the first col.
     */
    Iterator iteratesRowCol(bool reversedRow = false , bool reversedCol = false) // row ++ follow by col ++
    {
        Grid start = Grid(0,0);
        Grid end = Grid(_row,_col);
        if(reversedRow)
        {
            start.row = _row-1;
            end.row = -1;
        }
        if(reversedCol)
        {
            start.col = _col-1;
            end.col = -1;
        }
        return Iterator(start,end, this, false);
    }
    /**
     * Iterates a subspace of the 2D space row follow by col
     * The direction of iteration is will depend on the start end grid.
     */
    Iterator iteratesRowCol(Grid start, Grid end)
    {
        return Iterator(start,end,this,false);
    }
    // public read only value.
    const int &row;
    const int &col;
private:
    std::vector<std::vector<T> > _2dspace;
    T _defaultValue;
    int _row;
    int _col;
    // initialization
    void init(int row, int col, T defaultValue)
    {
        _2dspace = std::vector<std::vector<T> >(row, std::vector<T>(col));
        for(int r = 0 ; r < row ; r++)
        {
            for(int c = 0 ; c < col ; c++)
            {
                _2dspace[r][c] = defaultValue;
            }
        }
        this->_defaultValue = defaultValue;
        this->_row = row;
        this->_col = col;
    }
};

#endif
