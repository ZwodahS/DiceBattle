#ifndef _GAME_LOGIC_DIE_H_
#define _GAME_LOGIC_DIE_H_
#include "../constants.hpp"
#include <vector>
#include <SFML/Network.hpp>
class Die
{
public:
    Die();
    Die(sf::Int32 id,std::vector<DieFace::eDieFace> faces);
    ~Die();
    // store the position of the die.
    sf::Int32 id;
    bool rolled;
    bool frozen;
    DieFace::eDieFace currentFace;
    std::vector<DieFace::eDieFace> faces;

    void setCurrentFace(sf::Int32 faceIndex);
    void roll();
};

sf::Packet& operator << (sf::Packet& packet, const Die& message);
sf::Packet& operator >> (sf::Packet& packet, Die& message);
#endif
