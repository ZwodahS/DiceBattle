#ifndef _GAME_CONSTANTS_ABILITYTYPE_H_
#define _GAME_CONSTANTS_ABILITYTYPE_H_
#include <SFML/Network.hpp>
namespace AbilityType
{
    enum eAbilityType
    {
        None,
        PhysicalDamage,
        MagicalDamage,
        Shield,
        Heal,
        Burn,
        Freeze,
        Shock,
    };
    sf::Int32 toInt(eAbilityType type);
    eAbilityType toAbilityType(sf::Int32 intValue);
}

sf::Packet& operator << (sf::Packet& packet, const AbilityType::eAbilityType& message);
sf::Packet& operator >> (sf::Packet& packet, AbilityType::eAbilityType& message);
#endif
