#ifndef UFO_H
#define UFO_H

#include <array>
#include <SFML/Graphics.hpp>

class UFO
{
private:
    static constexpr unsigned ALIVE_TXTR_X = 382;
    static constexpr unsigned ALIVE_TXTR_Y = 33;
    static constexpr unsigned ALIVE_TXTR_WIDTH = 86;
    static constexpr unsigned ALIVE_TXTR_HEIGHT = 38;
    
    static constexpr unsigned DEAD_TXTR_X = 555;
    static constexpr unsigned DEAD_TXTR_Y = 107;
    static constexpr unsigned DEAD_TXTR_WIDTH = 48;
    static constexpr unsigned DEAD_TXTR_HEIGHT = 27;

    static constexpr unsigned Y = 125;
    static constexpr unsigned SPEED = 3;

    // The UFO appears at a 1/APPEAR_CHANCE rate.
    static constexpr unsigned APPEAR_CHANCE = 500;

    // UFO has 3 possible score values (defined in constructor initializer)
    const std::array<unsigned, 3> SCORES;

    sf::Image &spritesheet;
    sf::Texture alive_txtr;
    sf::Texture dead_txtr;
    sf::Sprite sprite;

    bool on_screen;

    bool toAppearOrNah();
    void appear();

public:
    UFO(sf::Image &spritesheet);

    void move();
    void update();
    void draw(sf::RenderWindow &window);

};

#endif
