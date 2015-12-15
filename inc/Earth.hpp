#ifndef EARTH_H
#define EARTH_H

#include <SFML/Graphics.hpp>

/* The little line at the bottom of the screen. Everything you are fighting for! */

class Earth
{
private:
    static constexpr unsigned HEIGHT = 2;
    static constexpr unsigned X = 0;
    static constexpr unsigned Y = 680;

    sf::RectangleShape shape;

public:
    Earth(const unsigned screenw);
    const sf::RectangleShape& getShape() const { return this->shape; }

};

#endif
