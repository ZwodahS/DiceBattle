#ifndef _GAME_SCREENS_ABILITYSCREEN_H_
#define _GAME_SCREENS_ABILITYSCREEN_H_
#include "../logic/Rules.hpp"
#include "../../z_framework/zf_sfml/Button.hpp"
#include "Screen.hpp"
#include <vector>
class AbilityScreen : public Screen
{
public:
    AbilityScreen(Game& game, Rules& rules);
    ~AbilityScreen();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void textInput(char c);

    void setRule(Rules& rule);
private:
    Rules* _rules;
    ////// Store it in pages like in the help screen //////
    ///// page one stores the 6 dice and the starting Hp /////
    ///// Page two onwards display the abilities starting from the lower cost.
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::Text> _texts;
    int _currentPage; 
    int _maxPage;

    void loadPage(int page);
    void loadDicePage();
    void loadAbilities(int start, int end);

    zf::Button _nextButton;
    zf::Button _previousButton;
    zf::Button _closeButton;
    void nextPage();
    void previousPage();
    void populateAbility(const Ability ability, int position);
};
#endif
