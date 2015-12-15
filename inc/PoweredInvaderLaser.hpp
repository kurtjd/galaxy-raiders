#ifndef POWEREDINVADERLASER_H
#define POWEREDINVADERLASER_H

#include "InvaderLaser.hpp"

/* A powered laser moves faster and does more damage to shields. */

class PoweredInvaderLaser : public InvaderLaser
{
private:

public:
    PoweredInvaderLaser(const unsigned x, const unsigned y);

    void move();
    void draw(sf::RenderWindow &window);

    // Overload checkCollide method to allow rect or point
    bool checkCollide(const unsigned x, const unsigned y) const;
    bool checkCollide(const sf::FloatRect rect) const;

};

#endif
