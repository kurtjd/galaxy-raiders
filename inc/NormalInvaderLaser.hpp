#ifndef NORMALINVADERLASER_H
#define NORMALINVADERLASER_H

#include "InvaderLaser.hpp"

/* A normal laser fired by Invaders. This is slower and less powerful than the
 * lightning-shaped 'Powered' laser. */

class NormalInvaderLaser : public InvaderLaser
{
private:
    static constexpr unsigned HEIGHT = 15;
    static constexpr unsigned WIDTH = 12;
    static constexpr unsigned THICKNESS = 2;
    static constexpr double h_part_moverate = 1.3; // Speed the horz part moves relative to the vert part.

    // Shapes that make up a normal laser.
    sf::RectangleShape v_part;
    sf::RectangleShape h_part;

    int h_part_movedir; // Direction the horz part is moving.

    // Used to animate the horizontal part moving up and down.
    void moveHPart();

public:
    NormalInvaderLaser(const unsigned x, const unsigned y, const unsigned shield_line, const bool will_hurt, Invader &owner);
    virtual ~NormalInvaderLaser(){}

    virtual unsigned getX() const;
    virtual unsigned getY() const;
    virtual void move();
    virtual void draw(sf::RenderWindow &window);

    // Overload checkCollide method to allow rect or point
    virtual bool checkCollide(const unsigned x, const unsigned y) const;
    virtual bool checkCollide(const sf::FloatRect rect) const;

};

#endif
