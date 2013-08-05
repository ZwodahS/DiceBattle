#include "Die.hpp"

Die::Die()
    :id(0), currentFace(DieFace::Sword)
{

}

Die::Die(sf::Int32 i, std::vector<DieFace::eDieFace> f)
    :id(i), faces(f), currentFace(f.size () > 0 ? f[0] : DieFace::Sword)
{
}

Die::~Die()
{
}

void Die::setCurrentFace(sf::Int32 faceIndex)
{
    if(faceIndex >= 0 || faceIndex < faces.size())
    {
        currentFace = faces[faceIndex];
    }
}

void Die::roll()
{
    sf::Int32 r = rand() % faces.size(); 
    currentFace = faces[r];
}

sf::Packet& operator << (sf::Packet& packet, const Die& message)
{
    packet << message.id << message.currentFace;
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
    packet >> message.id >> message.currentFace;;
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
