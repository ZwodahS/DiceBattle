#ifndef _GAME_LOGIC_ABILITYEFFECT_H_
#define _GAME_LOGIC_ABILITYEFFECT_H_
#include "../constants.hpp"
#include <SFML/Network.hpp>
struct AbilityEffect
{
    /**
     * Type of ability
     */
    AbilityType::eAbilityType type;
    /**
     * For value, it means different things for different effect.
     * For PhysicalDamage and MagicalDamage, the value corresponds to the value dealt.
     * For Shield, the value is the value of the shield gained.
     * For Heal, the value is the amount of health gained.
     * For Burn, the value is the value of the burnCounter added to the enemy.
     * For Freeze, the value is the number of dice locked.
     * For Shock, the number of dice lost.
     *
     */
    sf::Int32 value;
    AbilityEffect();
    AbilityEffect(AbilityType::eAbilityType type, sf::Int32 value);
};

sf::Packet& operator << (sf::Packet& packet, const AbilityEffect& message);
sf::Packet& operator >> (sf::Packet& packet, AbilityEffect& message);
std::ostream& operator << (std::ostream& stream, const AbilityEffect& effect);
bool operator==(const AbilityEffect& lhs, const AbilityEffect& rhs);
bool operator!=(const AbilityEffect& lhs, const AbilityEffect& rhs);

#endif
