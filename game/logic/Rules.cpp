#include "Rules.hpp"

Rules::Rules()
    :_loaded(false)
{
}

Rules::Rules(std::vector<Ability> abilities, sf::Int32 unitHp, std::vector<Die> dice)
    :_startingHp(unitHp), _abilities(abilities), _dice(dice), _loaded(true)
{
}

void Rules::overwrite(std::vector<Ability> abilities, sf::Int32 unitHp, std::vector<Die> dice)
{
    this->_abilities = abilities;
    this->_startingHp = unitHp;
    this->_dice = dice;
}
sf::Packet& operator << (sf::Packet& packet, const Rules& message)
{
    packet << message.getStartingHp();
    const std::vector<Die>& dice = message.getDice();
    sf::Int32 size = dice.size();
    packet << size;
    for(std::vector<Die>::const_iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        packet << *it; 
    }
    const std::vector<Ability>& abilities = message.getAbilities();
    size = abilities.size();
    packet << size;
    for(std::vector<Ability>::const_iterator it = abilities.begin() ; it != abilities.end() ; ++it)
    {
        packet << *it; 
    }
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, Rules& message)
{
    sf::Int32 startingHp;
    sf::Int32 size;
    packet >> startingHp >> size;
    std::vector<Die> dice;
    std::vector<Ability> abilities;
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        Die d;
        packet >> d;
        dice.push_back(d);
    }
    packet >> size;
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        Ability a;
        packet >> a;
        abilities.push_back(a);
    }
    message.overwrite(abilities, startingHp, dice);
    return packet;
}
sf::Int32 Rules::getStartingHp() const
{
    return _startingHp;
}
const std::vector<Die>& Rules::getDice() const
{
    return _dice;
}
const std::vector<Ability>& Rules::getAbilities() const
{
    return _abilities;
}
