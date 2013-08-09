#include "Button.hpp"
namespace zf
{
    Button::Button()
        :clickBound(_clickBound),selected(_selected),_selected(false)
    {
    }
    
    Button::Button(const Button& button)
        :clickBound(_clickBound), selected(_selected),
        selectedSprite(button.selectedSprite), unselectedSprite(button.unselectedSprite), 
        _selected(button.selected), _clickBound(button._clickBound)
    {

    }

    Button::Button(sf::Sprite ss, sf::Sprite us, sf::FloatRect size)
        :selected(_selected), clickBound(_clickBound), _clickBound(size),
        selectedSprite(ss), unselectedSprite(us)     
    {
    }

    Button::~Button()
    {
    }

    void Button::setPosition(sf::Vector2f position)
    {
        selectedSprite.setPosition(position);
        unselectedSprite.setPosition(position);
        _clickBound.left = position.x;
        _clickBound.top = position.y;
    }
        
    void Button::updateSelection(sf::Vector2f mousePos)
    {
        setSelected(clickBound.contains(mousePos));
    }

    void Button::setSelected(bool s)
    {
        this->_selected = s;
    }

    void Button::draw(sf::RenderWindow& window, sf::Time delta)
    {
        if(_selected)
        {
            window.draw(selectedSprite);
        }
        else
        {
            window.draw(unselectedSprite);
        }
    }
    
    Button& Button::operator=(const Button &rhs)
    {
        this->selectedSprite = rhs.selectedSprite;
        this->unselectedSprite = rhs.unselectedSprite;
        this->_selected = rhs.selected;
        this->_clickBound = rhs._clickBound;
    }

}
