#ifndef NORMALINVADERLASER_H
#define NORMALINVADERLASER_H

#include "InvaderLaser.hpp"

/* A normal laser fired by Invaders. This is slower and less powerful than the
 * lightning-shaped 'Powered' laser. */

class NormalInvaderLaser : public InvaderLaser
{
private:
    // Shapes that make up a normal laser.
    sf::RectangleShape v_part;
    sf::RectangleShape h_part;

public:
    NormalInvaderLaser(const unsigned x, const unsigned y);

    void move();
    void draw(sf::RenderWindow &window);

    // Overload checkCollide method to allow rect or point
    bool checkCollide(const unsigned x, const unsigned y) const;
    bool checkCollide(const sf::FloatRect rect) const;

};

#endif
