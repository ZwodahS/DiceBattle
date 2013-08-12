#include "Ability.hpp"
#include <iostream>
Ability::Ability(sf::Int32 abilityId, std::string abilityName)
    :id(abilityId), name(abilityName) 
{
}

Ability::~Ability()
{
}

bool Ability::canUseAbility(const std::vector<Die>& dice) const
{
    return match(dice).size() > 0 ;
}
bool Ability::canStrictlyUseAbility(const std::vector<Die>& dice) const
{
    std::vector<sf::Int32> matches = match(dice);
    if(matches.size() != dice.size())
    {
        return false;
    }
    return true;
}

std::vector<Die> Ability::matchDice(const std::vector<Die>& dice) const
{
    std::vector<Die> outs;
    std::vector<DieFace::eDieFace> tmpCosts = this->costs; // copy the cost
    // iterate the dice given
    for(std::vector<Die>::const_iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        for(int i = 0 ; i < tmpCosts.size() ; i++)
        {
            if(tmpCosts[i] == (*it).faces[(*it).currentFaceId])
            {
                outs.push_back((*it));
                tmpCosts.erase(tmpCosts.begin() + i);
                break;
            }
        }
        if(tmpCosts.size() == 0)
        {
            break;
        }
    }
    if(tmpCosts.size() != 0)
    {
        return std::vector<Die>();
    }
    else
    {
        return outs;
    }
}

std::vector<sf::Int32> Ability::match(const std::vector<Die>& dice) const
{
    std::vector<sf::Int32> outs;
    std::vector<DieFace::eDieFace> tmpCosts = this->costs; // copy the cost
    // iterate the dice given
    for(std::vector<Die>::const_iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        for(int i = 0 ; i < tmpCosts.size() ; i++)
        {
            if(tmpCosts[i] == (*it).faces[(*it).currentFaceId])
            {
                outs.push_back((*it).id);
                tmpCosts.erase(tmpCosts.begin() + i);
                break;
            }
        }
        if(tmpCosts.size() == 0)
        {
            break;
        }
    }
    if(tmpCosts.size() != 0)
    {
        return std::vector<sf::Int32>();
    }
    else
    {
        return outs;
    }
}

sf::Packet& operator << (sf::Packet& packet, const Ability& message)
{
    packet << message.id << message.name;
    sf::Int32 size = message.costs.size();
    packet << size;
    for(std::vector<DieFace::eDieFace>::const_iterator it = message.costs.begin() ; it != message.costs.end() ; ++it)
    {
        packet << *it; 
    }
    size = message.effects.size();
    packet << size;
    for(std::vector<AbilityEffect>::const_iterator it = message.effects.begin() ; it != message.effects.end() ; ++it)
    {
        packet << *it;
    }
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, Ability& message)
{
    packet >> message.id >> message.name;
    sf::Int32 size;
    packet >> size;
    message.costs.clear();
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        DieFace::eDieFace f;
        packet >> f;
        message.costs.push_back(f);
    }
    message.effects.clear();
    packet >> size;
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        AbilityEffect e;
        packet >> e;
        message.effects.push_back(e);
    }
    return packet;
}

bool operator==(const Ability& lhs, const Ability& rhs)
{
    // compare the id && name
    if(lhs.id != rhs.id || lhs.name != rhs.name)
    {
        return false;
    }
    // check size of cost and effects
    if(lhs.costs.size() != rhs.costs.size() || lhs.effects.size() != rhs.effects.size())
    {
        return false;
    } 
    // check every thing matches
    for(int i = 0 ; i < lhs.costs.size() ; i++)
    {
        if(lhs.costs[i] != rhs.costs[i])
        {
            return false;
        }
    }
    for(int i = 0 ; i < lhs.effects.size() ; i++)
    {
        if(lhs.effects[i] != rhs.effects[i])
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const Ability& lhs, const Ability& rhs)
{
    return !(lhs == rhs);
}
