#ifndef INVADERLASER_H
#define INVADERLASER_H

#include <SFML/Graphics.hpp>

/* The laser shot by Space Invaders. */

class InvaderLaser
{
// The powered laser looks like a lightning bolt and does more damage to shields
public: enum LaserType { NORMAL, POWERED };

private:
    static const int SPEED = 10;

    sf::Image &spritesheet;
    sf::Texture txtr;
    sf::Sprite sprite;

    LaserType type;

    unsigned shield_dmg; // How much damage it does to shields

public:
    InvaderLaser(sf::Image &spritesheet, LaserType type, unsigned x, unsigned y);
    sf::Sprite& getSprite(){ return this->sprite; }

    void move();

};

#endif
