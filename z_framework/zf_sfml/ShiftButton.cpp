#include "ShiftButton.hpp"
#include <iostream>
namespace zf
{
    ShiftButton::ShiftButton()
        :bound(_bound)
    {
    }

    ShiftButton::ShiftButton(const ShiftButton& shiftButton)
        : bound(_bound), _sprite(shiftButton._sprite), _actualPosition(shiftButton._actualPosition)
        , _currentPosition(shiftButton._currentPosition), _shiftMax(shiftButton._shiftMax), _bound(shiftButton._bound)
        , _currentShift(shiftButton._currentShift), _shiftDuration(shiftButton._shiftDuration)
    {
    }

    ShiftButton::ShiftButton(sf::Sprite buttonSprite, sf::Vector2f shiftMax, float shiftDuration)
        : bound(_bound), _sprite(buttonSprite), _actualPosition(0,0), _currentPosition(0,0), _shiftMax(shiftMax)
        , _shiftDuration(shiftDuration)
    {
        updateShift();
    }

    ShiftButton::~ShiftButton()
    {
    }

    void ShiftButton::setPosition(sf::Vector2f position)
    {
        // set the actual position
        _actualPosition = position;
        updateShift();
    }

    void ShiftButton::updateSelection(const sf::Vector2f& mousePosition, const sf::Time& delta)
    {
        if(bound.contains(mousePosition))
        {
            if(_shiftMax != _currentShift)
            {
                _currentShift.x += _shiftMax.x * (delta.asSeconds() / _shiftDuration);
                _currentShift.y += _shiftMax.y * (delta.asSeconds() / _shiftDuration);
                if(_shiftMax.x > 0)
                {
                    if(_currentShift.x > _shiftMax.x)
                    {
                        _currentShift.x = _shiftMax.x;
                    }
                }
                else if(_shiftMax.x < 0)
                {
                    if(_currentShift.x < _shiftMax.x)
                    {
                        _currentShift.x = _shiftMax.x;
                    }
                }
                if(_shiftMax.y > 0)
                {
                    if(_currentShift.y > _shiftMax.y)
                    {
                        _currentShift.y = _shiftMax.y;
                    }
                }
                else if(_shiftMax.y < 0)
                {
                    if(_currentShift.y < _shiftMax.y)
                    {
                        _currentShift.y = _shiftMax.y;
                    }
                }
            }
        } 
        else
        {
            if(_currentShift != sf::Vector2f(0,0))
            {
                _currentShift.x -= _shiftMax.x * (delta.asSeconds() / _shiftDuration);
                _currentShift.y -= _shiftMax.y * (delta.asSeconds() / _shiftDuration);
                if(_shiftMax.x > 0)
                {
                    if(_currentShift.x < 0)
                    {
                        _currentShift.x = 0;
                    }
                }
                else if(_shiftMax.x < 0)
                {
                    if(_currentShift.x > 0 )
                    {
                        _currentShift.x = 0;
                    }
                }
                if(_shiftMax.y > 0)
                {
                    if(_currentShift.y < 0)
                    {
                        _currentShift.y = 0;
                    }
                }
                else if(_shiftMax.y < 0)
                {
                    if(_currentShift.y > 0)
                    {
                        _currentShift.y = 0;
                    }
                }
            }
        }
        updateShift();
    }

    void ShiftButton::draw(sf::RenderWindow& window, const sf::Time& delta)
    {
        window.draw(_sprite);
    }

    ShiftButton& ShiftButton::operator= (const ShiftButton& rhs)
    {
        _sprite = rhs._sprite;
        _actualPosition = rhs._actualPosition;
        _currentPosition = rhs._currentPosition;
        _currentShift = rhs._currentShift;
        _shiftMax = rhs._shiftMax;
        _bound = rhs._bound;
    }
    void ShiftButton::updateShift()
    {
        // add the shift to actual position to give current position
        _currentPosition = _actualPosition + _currentShift;
        _sprite.setPosition(_currentPosition);
        _bound = _sprite.getGlobalBounds();
    }
    void ShiftButton::setAlpha(float alpha)
    {
        zf::setAlpha(_sprite, alpha);
    }
    void ShiftButton::move(sf::Vector2f move)
    {
        setPosition(_actualPosition + move);
    }
    void ShiftButton::setColor(sf::Color color)
    {
        _sprite.setColor(color);
    }
    sf::Vector2f ShiftButton::getPosition()
    {
        return sf::Vector2f(_bound.left, _bound.top);
    }
}
