#ifndef LIVESDISPLAY_H
#define LIVESDISPLAY_H

#include <vector>
#include <SFML/Graphics.hpp>

class LivesDisplay
{
private:
    static constexpr unsigned X = 0;
    static constexpr unsigned Y = 685;

    static constexpr unsigned CANNON_TXTR_X_START = 492;
    static constexpr unsigned CANNON_TXTR_Y_START = 40;
    static constexpr unsigned CANNON_TXTR_WIDTH = 48;
    static constexpr unsigned CANNON_TXTR_HEIGHT = 30;

    static constexpr unsigned LIVES_START = 3;

    sf::Image &spritesheet;
    sf::Texture cannon_txtr;

    // A sprite is made for each life left so it can be displayed.
    std::vector<sf::Sprite*> cannons;

    //Current number of lives left.
    unsigned lives;

    // Sets up the cannon sprites.
    void initCannons();

public:
    LivesDisplay(sf::Image &spritesheet);
    ~LivesDisplay();

    unsigned getLives() const { return this->lives; }

    void draw(sf::RenderWindow &window);

};

#endif
