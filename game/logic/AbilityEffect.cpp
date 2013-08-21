#include "AbilityEffect.hpp"
AbilityEffect::AbilityEffect()
    :type(AbilityType::None), value(0)
{
}

AbilityEffect::AbilityEffect(AbilityType::eAbilityType t, sf::Int32 v)
    :type(t), value(v)
{
}

sf::Packet& operator << (sf::Packet& packet, const AbilityEffect& message)
{
    return packet << message.type << message.value;
}
sf::Packet& operator >> (sf::Packet& packet, AbilityEffect& message)
{
    return packet >> message.type >> message.value;
}

bool operator==(const AbilityEffect& lhs, const AbilityEffect& rhs)
{
    if(lhs.type != rhs.type || lhs.value != rhs.value)
    {
        return false;
    }
    return true;
}

bool operator!=(const AbilityEffect& lhs, const AbilityEffect& rhs)
{
    return !(lhs == rhs);
}
std::ostream& operator << (std::ostream& stream, const AbilityEffect& effect)
{
    stream << AbilityType::toString(effect.type) << " " << effect.value;
    return stream;
}
