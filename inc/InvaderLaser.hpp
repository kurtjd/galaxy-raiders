#ifndef INVADERLASER_H
#define INVADERLASER_H

#include <SFML/Graphics.hpp>
#include "../inc/globals.hpp"

/* The laser shot by Space Invaders. */

class InvaderLaser
{
// The powered laser looks like a lightning bolt and does more damage to shields
public: enum LaserType { NORMAL, POWERED };

private:
    static constexpr int SPEED = 5;

    sf::Image &spritesheet;
    sf::Texture txtr;
    sf::Sprite sprite;

    /* Normal Laser Info */

    LaserType type;

    bool hit; // Whether or not hit something and about to be removed.
    unsigned shield_dmg; // How much damage it does to shields

public:
    InvaderLaser(sf::Image &spritesheet, const LaserType type, const unsigned x, const unsigned y);
    sf::Sprite& getSprite(){ return this->sprite; }
    bool isHit() const { return this->hit; }
    unsigned getDmg() const { return this->shield_dmg; }

    void remove();
    void move();

};

#endif
