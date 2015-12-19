#ifndef UFO_H
#define UFO_H

#include <array>
#include <SFML/Graphics.hpp>
#include "../inc/Textures.hpp"

class UFO
{
private:
    static constexpr unsigned Y = 125;
    static constexpr unsigned SPEED = 3;

    // The UFO appears at a 1/APPEAR_CHANCE rate.
    static constexpr unsigned APPEAR_CHANCE = 500;

    // UFO has 3 possible score values (defined in constructor initializer)
    const std::array<unsigned, 3> SCORES;

    sf::Sprite sprite;

    bool on_screen;

    bool toAppearOrNah();
    void appear();

public:
    UFO(const Textures &textures);

    void move();
    void update();
    void draw(sf::RenderWindow &window);

};

#endif
