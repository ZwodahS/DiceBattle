#include "Unit.hpp"

Unit::Unit()
    :currentHp(0), maxHp(0), burnCounter(0), shieldCounter(0), diceCounter(0)
{
}

Unit::Unit(sf::Int32 hp, sf::Int32 dice)
    :currentHp(hp), maxHp(hp), burnCounter(0), shieldCounter(0), diceCounter(dice)
{
}

Unit::~Unit()
{
}
