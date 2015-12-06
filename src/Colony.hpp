#ifndef COLONY_H
#define COLONY_H

#include <SFML/Graphics.hpp>

class Colony
{
private:
    sf::RectangleShape shape;

public:
    Colony(unsigned screenw);
    sf::RectangleShape& getShape(){ return this->shape; }

};

#endif
