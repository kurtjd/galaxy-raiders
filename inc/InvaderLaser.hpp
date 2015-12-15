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

    /* Normal Laser Info */
    sf::RectangleShape v_part;
    sf::RectangleShape h_part;

    LaserType type;

    bool hit; // Whether or not hit something and about to be removed.
    unsigned shield_dmg; // How much damage it does to shields

    /* Normal Laser Methods */
    void createNormLaser(const unsigned x, const unsigned y);

    template<typename T>
    bool checkCollideNormLaser(const sf::Rect<T> rect) const;
    bool checkCollideNormLaser(const unsigned x, const unsigned y) const;

    void moveNormLaser();
    void drawNormLaser(sf::RenderWindow &window);

public:
    InvaderLaser(const LaserType type, const unsigned x, const unsigned y);
    bool isHit() const { return this->hit; }
    unsigned getDmg() const { return this->shield_dmg; }

    void remove();
    void move();
    void draw(sf::RenderWindow &window);

    // Use template to allow any kind of rect, IE: IntRect, FloatRect, etc
    // Overload method to allow rect or point
    template<typename T>
    bool checkCollide(const sf::Rect<T> rect) const;
    bool checkCollide(const unsigned x, const unsigned y) const;

};

// Implement the templated methods here so as not to clutter the header file.
// Apparently templated methods need to have their implementation included everywhere they are used.
#include "InvaderLaser.tpp"

#endif
