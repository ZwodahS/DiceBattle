#ifndef _GAME_SCREENS_HELPSCREEN_H_
#define _GAME_SCREENS_HELPSCREEN_H_
#include "../../z_framework/zf_sfml/Button.hpp"
#include "Screen.hpp"
/**
 * This is a extremely bad way to do a help screen but I really have no idea how to do it in a better way
 * without writing too much framework code. 
 */
class Game;
class HelpScreen : Screen
{
public:
    HelpScreen(Game& game);
    ~HelpScreen();

    void draw(sf::RenderWindow& window, const sf::Time& delta);
    void update(sf::RenderWindow& window, const sf::Time& delta, const bool& handleInput);
    void textInput(char c);
private:
    //////// Page One /////////
    std::vector<sf::Sprite> _pageOneSprites;
    std::vector<sf::Text> _pageOneTexts;
    void loadPageOne();
    //////// Page Two /////////
    std::vector<sf::Sprite> _pageTwoSprites;
    std::vector<sf::Text> _pageTwoTexts;
    void loadPageTwo();
    //////// Page Three /////////
    std::vector<sf::Sprite> _pageThreeSprites;
    std::vector<sf::Text> _pageThreeTexts;
    void loadPageThree();
    int _currentPage;

    void nextPage();
    void previousPage();

    zf::Button _nextButton;
    zf::Button _previousButton;
    zf::Button _closeButton;
};
#endif
