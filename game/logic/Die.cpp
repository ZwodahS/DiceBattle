#include "Die.hpp"

Die::Die()
    :id(-1), currentFaceId(0), frozen(false), rolled(false)
{

}

Die::Die(sf::Int32 i, std::vector<DieFace::eDieFace> f)
    :id(i), faces(f), currentFaceId(f.size () > 0 ? f[0] : 0), frozen(false), rolled(false)
{
}

Die::~Die()
{
}

void Die::setCurrentFace(sf::Int32 faceIndex)
{
    if(faceIndex >= 0 || faceIndex < faces.size())
    {
        currentFaceId = faceIndex;
    }
}

void Die::roll()
{
    if(!frozen)
    {
        sf::Int32 r = rand() % faces.size(); 
        currentFaceId = r;
        rolled = true;
    }
}

sf::Packet& operator << (sf::Packet& packet, const Die& message)
{
    packet << message.id << message.currentFaceId << message.frozen << message.rolled;
    sf::Int32 size = message.faces.size();
    packet << size;
    for(std::vector<DieFace::eDieFace>::const_iterator it = message.faces.begin() ; it != message.faces.end() ; ++it)
    {
        packet << *it; 
    }
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, Die& message)
{
    packet >> message.id >> message.currentFaceId >> message.frozen >> message.rolled;
    sf::Int32 size;
    packet >> size;
    message.faces.clear();
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        DieFace::eDieFace tmp;
        packet >> tmp;
        message.faces.push_back(tmp);
    }
    return packet;
}
