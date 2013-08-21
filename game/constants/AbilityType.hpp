#ifndef _GAME_CONSTANTS_ABILITYTYPE_H_
#define _GAME_CONSTANTS_ABILITYTYPE_H_
#include <SFML/Network.hpp>
namespace AbilityType
{
    enum eAbilityType
    {
        None = 0,
        PhysicalDamage = 1,
        MagicalDamage = 2,
        Shield = 3,
        Heal = 4,
        Burn = 5,
        Freeze = 6,
        Shock = 7,
    };
    sf::Int32 toInt(eAbilityType type);
    std::string toString(eAbilityType type);
    eAbilityType toAbilityType(sf::Int32 intValue);
}

sf::Packet& operator << (sf::Packet& packet, const AbilityType::eAbilityType& message);
sf::Packet& operator >> (sf::Packet& packet, AbilityType::eAbilityType& message);
#endif
