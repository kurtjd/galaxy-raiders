#ifndef INVADERLASER_H
#define INVADERLASER_H

#include <SFML/Graphics.hpp>

class InvaderLaser
{
public: enum LaserType { NORMAL, POWERED };

private:
    static const int SPEED = 10;

    sf::Image &spritesheet;
    sf::Texture txtr;
    sf::Sprite sprite;

    LaserType type;

public:
    InvaderLaser(sf::Image &spritesheet, LaserType type, unsigned x, unsigned y);
    sf::Sprite& getSprite(){ return this->sprite; }

};

#endif
