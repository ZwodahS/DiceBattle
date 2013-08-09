#ifndef _GAME_LOGIC_RULES_H_
#define _GAME_LOGIC_RULES_H_
#include "Ability.hpp"
#include "Die.hpp"
#include <SFML/Network.hpp>
/**
 * Rule class stores the list of ability that is allowed in the game.
 * It also stores the default hp of unit.
 * It also stores the 6 dice that is used. 
 */
class Rules
{
public:
    Rules();
    Rules(std::vector<Ability> abilities, sf::Int32 unitHp, std::vector<Die> dice);
    void overwrite(std::vector<Ability> abilities, sf::Int32 unitHp, std::vector<Die> dice);
    sf::Int32 getStartingHp() const;

    bool containsAbility(const Ability& ability) const;
    const std::vector<Die>& getDice() const;
    const std::vector<Ability>& getAbilities() const;
    
    bool loadFromFile(std::string filename);
    bool isLoaded();
    void sortAbilities();
private:
    sf::Int32 _startingHp;
    std::vector<Ability> _abilities;
    std::vector<Die> _dice;
    
    bool _loaded;
};
sf::Packet& operator << (sf::Packet& packet, const Rules& message);
sf::Packet& operator >> (sf::Packet& packet, Rules& message);
#endif
