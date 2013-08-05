#include "Ability.hpp"

Ability::Ability(sf::Int32 abilityId, std::string abilityName)
    :id(abilityId), name(abilityName) 
{
}

Ability::~Ability()
{
}

bool Ability::canUseAbility(const std::vector<Die>& dices) const
{
    return match(dices).size() > 0 ;
}

std::vector<sf::Int32> Ability::match(const std::vector<Die>& dices) const
{
    std::vector<sf::Int32> outs;
    std::vector<DieFace::eDieFace> costs = costs; // copy the cost
    // iterate the dice given
    for(std::vector<Die>::const_iterator it = dices.begin() ; it != dices.end() ; ++it)
    {
        for(int i = 0 ; i < costs.size() ; i++)
        {
            if(costs[i] == (*it).currentFace)
            {
                outs.push_back((*it).id);
                costs.erase(costs.begin() + i);
                break;
            }
        }
        if(costs.size() == 0)
        {
            break;
        }
    }
    if(costs.size() != 0)
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
