#include "Rules.hpp"
#include <fstream>
#include "../../z_framework/zf_common/f_conversion.hpp"
#include <algorithm>
Rules::Rules()
    :_loaded(false)
{
}

Rules::Rules(std::vector<Ability> abilities, sf::Int32 unitHp, std::vector<Die> dice)
    :_startingHp(unitHp), _abilities(abilities), _dice(dice), _loaded(true)
{
}

void Rules::overwrite(std::vector<Ability> abilities, sf::Int32 unitHp, std::vector<Die> dice)
{
    this->_abilities = abilities;
    this->_startingHp = unitHp;
    this->_dice = dice;
}
sf::Packet& operator << (sf::Packet& packet, const Rules& message)
{
    packet << message.getStartingHp();
    const std::vector<Die>& dice = message.getDice();
    sf::Int32 size = dice.size();
    packet << size;
    for(std::vector<Die>::const_iterator it = dice.begin() ; it != dice.end() ; ++it)
    {
        packet << *it; 
    }
    const std::vector<Ability>& abilities = message.getAbilities();
    size = abilities.size();
    packet << size;
    for(std::vector<Ability>::const_iterator it = abilities.begin() ; it != abilities.end() ; ++it)
    {
        packet << *it; 
    }
    return packet;
}
sf::Packet& operator >> (sf::Packet& packet, Rules& message)
{
    sf::Int32 startingHp;
    sf::Int32 size;
    packet >> startingHp >> size;
    std::vector<Die> dice;
    std::vector<Ability> abilities;
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        Die d;
        packet >> d;
        dice.push_back(d);
    }
    packet >> size;
    for(sf::Int32 i = 0 ; i < size ; i++)
    {
        Ability a;
        packet >> a;
        abilities.push_back(a);
    }
    message.overwrite(abilities, startingHp, dice);
    return packet;
}
sf::Int32 Rules::getStartingHp() const
{
    return _startingHp;
}
const std::vector<Die>& Rules::getDice() const
{
    return _dice;
}
const std::vector<Ability>& Rules::getAbilities() const
{
    return _abilities;
}

bool Rules::loadFromFile(std::string filename)
{
    // reset all values
    _startingHp = 0;
    _dice.clear();
    _abilities.clear();
    _loaded = false;

    // temp variables to store.
    sf::Int32 startingHp;
    std::vector<Ability> abilities;
    std::vector<Die> dice;

    // open the file and make sure it is good to go
    std::ifstream file;
    file.open(filename.c_str());
    if(!file.is_open())
    {
        return false;
    }

    //prepare for reading    
    std::string line;
    // 0 for haven't read hp
    // 1 for reading dice
    // 2 for reading ability
    int state = 0;
    while(file.good() && state != -1)
    {
        getline(file, line);
        if(line[0] == '"' || line.size() == 0 || line[0] == ' ')
        {
            continue;
        }
        else if(state == 0)
        {
            if(!zf::toInt(line,startingHp))
            {
                std::cout << line << std::endl;
                //ILLEGAL HP .....
                std::cout << "illegal hp" << std::endl;
                state = -1;
                break;
            }
            state = 1;
        }
        else if(state == 1)
        {
            // check if the end of dice is reach
            if(line == "Ability")
            {
                state = 2;
            }
            else
            {
                //tokenize the faces
                std::vector<std::string> tokens = zf::tokenize(line);
                std::vector<DieFace::eDieFace> faces;
                // ensure that it is 6-sided
                if(tokens.size() != 6)
                {
                    std::cout << line << std::endl;
                    // ILLEGAL DICE SIDES
                    std::cout << "illegal dice side" << std::endl;
                    state = -1;
                    break;
                }
                else
                {
                    // iterate all the faces to convert int into DieFace::eDieFace
                    for(std::vector<std::string>::iterator it = tokens.begin() ; it != tokens.end() ; ++it)
                    {
                        sf::Int32 faceId;
                        if(!zf::toInt(*it,faceId))
                        {
                            std::cout << line << std::endl;
                            // Illegal face id
                            std::cout << "illegal face id" << std::endl;
                            state = -1;
                            break;
                        }
                        faces.push_back(DieFace::toDieFace(faceId));
                    }
                    dice.push_back(Die(dice.size(), faces));
                }
            }
        }
        else if(state == 2)
        {
            // I will need to read 3 lines here
            std::string costLine;
            std::string effectLine;
            if(!file.good())
            {
                std::cout << line << std::endl;
                std::cout << "Invalid number of lines for ability 1" << std::endl;
                state = -1;
                break;
            }
            getline(file, costLine);
            if(!file.good())
            {
                std::cout << "Invalid number of lines for ability 2" << std::endl;
                state = -1;
                break;
            }
            getline(file, effectLine);
            std::vector<DieFace::eDieFace> costs;
            std::vector<AbilityEffect> effects;
            //////// 
            // read all cost 
            Ability newAbility(abilities.size(), line);
            std::vector<std::string> costTokens = zf::tokenize(costLine);
            for(std::vector<std::string>::iterator it = costTokens.begin() ; it != costTokens.end() ; ++it)
            {
                sf::Int32 intValue;
                if(!zf::toInt(*it, intValue))
                {
                    std::cout << "Invalid cost" << std::endl;
                    state = -1;
                    break;
                }
                DieFace::eDieFace cost = DieFace::toDieFace(intValue);     
                newAbility.costs.push_back(cost);
            }
            if(state == -1)
            {
                break;
            }
            // this needs to be read in pairs
            std::vector<std::string> effectsToken = zf::tokenize(effectLine);
            for(int i = 0 ; i < effectsToken.size() ; i++)
            {
                // if there is no next element, then something is wrong
                if(i == effectsToken.size())
                {
                    std::cout << "Invalid effect length" << std::endl;
                    state = -1;
                    break;
                }
                std::string effectTypeString = effectsToken[i];
                i++;
                std::string valueString = effectsToken[i];
                sf::Int32 effectTypeInt;
                sf::Int32 valueInt;
                if(!zf::toInt(effectTypeString, effectTypeInt) || !zf::toInt(valueString, valueInt))
                {
                    std::cout << "Invalid effect or value" << std::endl;
                    state = -1;
                    break;
                }
                newAbility.effects.push_back(AbilityEffect(AbilityType::toAbilityType(effectTypeInt), valueInt));
            }
            if(state == -1)
            {
                break;
            }
            abilities.push_back(newAbility);
        }
    }
    // if state is 2 then means it has read the entire file (hopefully)
    if(state == 2)
    {
        overwrite(abilities, startingHp, dice);
        _loaded = true;
    }
    file.close();
    return _loaded;
}

bool ability_compare(const Ability& ability1, const Ability& ability2)
{
    return ability1.costs.size() > ability2.costs.size();
}

void Rules::sortAbilities()
{
    std::stable_sort(_abilities.begin(), _abilities.end(), ability_compare);
    for(sf::Int32 i = 0 ; i < _abilities.size() ; i++)
    {
        _abilities[i].id = i;
    }
}

bool Rules::containsAbility(const Ability& ability) const
{
    if(ability.id < 0 || ability.id >= _abilities.size())
    {
        return false;
    }
    return _abilities[ability.id] == ability;
}

std::vector<Ability> Rules::matchAbilities(std::vector<Die>& rolledDice, sf::Int32 count)
{
    std::vector<Die> tmp;
    return matchAbilities(rolledDice, tmp, count);
}

std::vector<Ability> Rules::matchAbilities(std::vector<Die>& rolledDice, std::vector<Die>& selectedDice, sf::Int32 count)
{
    std::vector<Ability> matchedAbilities;
    std::vector<Ability> secondaryAbilities;
    for(std::vector<Ability>::iterator it = _abilities.begin() ; it != _abilities.end() ; ++it)
    {
        if((*it).canUseAbility(selectedDice))
        {
            matchedAbilities.push_back(*it);
            if(matchedAbilities.size() == count)
            {
                break;
            }
        }
        else if((*it).canUseAbility(rolledDice))
        {
            secondaryAbilities.push_back(*it);
        }
    }
    // while there are still abilities in the secondary match and the matchAbilities is not enough.
    while(matchedAbilities.size() != count && secondaryAbilities.size() != 0)
    {
        matchedAbilities.push_back(secondaryAbilities[0]);
        secondaryAbilities.erase(secondaryAbilities.begin());
    }
    return matchedAbilities;
}
