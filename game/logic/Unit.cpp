#include "Unit.hpp"

Unit::Unit()
    :currentHp(0), maxHp(0), shieldCounter(0),
    burnCounter(0), freezeCounter(0), shockCounter(0), diceCounter(0), name("")
{
}

Unit::Unit(std::string n, sf::Int32 hp, sf::Int32 dice)
    :currentHp(hp), maxHp(hp), shieldCounter(0),
    burnCounter(0), freezeCounter(0), shockCounter(0), diceCounter(dice), name(n)
{
}

Unit::~Unit()
{
}

sf::Packet& operator << (sf::Packet& packet, const Unit& message)
{
    return packet << message.currentHp << message.maxHp << message.shieldCounter << message.burnCounter << message.freezeCounter << message.shockCounter << message.diceCounter << message.name;
}
sf::Packet& operator >> (sf::Packet& packet, Unit& message)
{
    return packet >> message.currentHp >> message.maxHp >> message.shieldCounter >> message.burnCounter >> message.freezeCounter >> message.shockCounter >> message.diceCounter >> message.name;
}
