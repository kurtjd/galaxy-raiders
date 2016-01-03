#ifndef POWEREDINVADERLASER_H
#define POWEREDINVADERLASER_H

#include "InvaderLaser.hpp"

/* A powered laser moves faster and does more damage to shields. */

class PoweredInvaderLaser : public InvaderLaser
{
private:
    static constexpr unsigned WIDTH = 2;
    static constexpr unsigned HEIGHT = 8;

    static constexpr unsigned FLIP_TICK_MAX = 7;

    sf::RectangleShape part1;
    sf::RectangleShape part2;
    sf::RectangleShape part3;
    sf::RectangleShape part4;

    unsigned flip_tick;

    // Makes the lightning bolt flip the way it faces.
    void flip();

public:
    PoweredInvaderLaser(const unsigned x, const unsigned y, const unsigned shield_line, const bool will_hurt, Invader &owner);
    virtual ~PoweredInvaderLaser(){}

    virtual unsigned getX() const;
    virtual unsigned getY() const;
    virtual void move();
    virtual void draw(sf::RenderWindow &window);

    // Overload checkCollide method to allow rect or point
    virtual bool checkCollide(const unsigned x, const unsigned y) const;
    virtual bool checkCollide(const sf::FloatRect rect) const;

};

#endif
