#include "AbilityType.hpp"
namespace AbilityType 
{
    sf::Int32 toInt(eAbilityType type)
    {
        return type;
    }
    eAbilityType toAbilityType(sf::Int32 intValue)
    {
        switch(intValue)
        {
            case None : return None;
            case PhysicalDamage: return PhysicalDamage;
            case MagicalDamage: return MagicalDamage;
            case Shield: return Shield;
            case Heal: return Heal;
            case Burn: return Burn;
            case Freeze: return Freeze;
            case Shock: return Shock;
            default : return None;
        }
    }
    std::string toString(eAbilityType type)
    {
        switch(type)
        {
            case None : return "None";
            case PhysicalDamage: return "PhysicalDamage";
            case MagicalDamage: return "MagicalDamage";
            case Shield: return "Shield";
            case Heal: return "Heal";
            case Burn: return "Burn";
            case Freeze: return "Freeze";
            case Shock: return "Shock";
            default : return "None";
        }
    }
}

sf::Packet& operator << (sf::Packet& packet, const AbilityType::eAbilityType& message)
{
    return packet << AbilityType::toInt(message);
}
sf::Packet& operator >> (sf::Packet& packet, AbilityType::eAbilityType& message)
{
    sf::Int32 tmp;
    packet >> tmp;
    message = AbilityType::toAbilityType(tmp);
    return packet ;
}
