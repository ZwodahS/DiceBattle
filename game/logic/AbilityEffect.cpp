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
