#ifndef EARTH_H
#define EARTH_H

#include <SFML/Graphics.hpp>

/* The little line at the bottom of the screen. Everything you are fighting for! */

class Earth
{
private:
    static const unsigned HEIGHT = 2;
    static const unsigned X = 0;
    static const unsigned Y = 680;

    sf::RectangleShape shape;

public:
    Earth(unsigned screenw);
    sf::RectangleShape& getShape(){ return this->shape; }

};

#endif
