#ifndef EARTH_H
#define EARTH_H

#include <SFML/Graphics.hpp>

class Earth
{
private:
    sf::RectangleShape shape;

public:
    Earth(unsigned screenw);
    sf::RectangleShape& getShape(){ return this->shape; }

};

#endif
