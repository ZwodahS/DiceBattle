#ifndef _GAME_LOGIC_ABILITY_H_
#define _GAME_LOGIC_ABILITY_H_
#include "Die.hpp"
#include "AbilityEffect.hpp"
#include <string>
#include <vector>
#include <SFML/Network.hpp>
/**
 * Stores the abilities that is available in the game.
 */
class Ability
{
public:

    Ability(sf::Int32 id = 0, std::string abilityName = "");
    ~Ability(); 
    /**
     * Check if the ability can be use given the rolled dice
     */
    bool canUseAbility(const std::vector<Die>& dices) const;
    /**
     * Find the list of die id from a list of dices that matches the cost.
     * If the dice given is not enough to use this ability, an empty list will be return.
     */
    std::vector<sf::Int32> match(const std::vector<Die>& dice) const;
    
    sf::Int32 id;
    std::string name;
    std::vector<DieFace::eDieFace> costs;
    std::vector<AbilityEffect> effects;
};

sf::Packet& operator << (sf::Packet& packet, const Ability& message);
sf::Packet& operator >> (sf::Packet& packet, Ability& message);

bool operator==(const Ability& lhs, const Ability& rhs);
bool operator!=(const Ability& lhs, const Ability& rhs);

#endif
