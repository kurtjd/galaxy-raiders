#ifndef SHIELDWALL_H
#define SHIELDWALL_H

#include <SFML/Graphics.hpp>
#include "Shield.hpp"

/* Controls behavior of each shield on screen.
 * Mainly just checks for collisions with lasers. */

typedef std::vector<Shield*> ShieldVector;

class ShieldWall
{
private:
    static constexpr unsigned Y = 520;

    // Where the first shield starts and the gap between subsequent shields
    static constexpr unsigned STARTX = 97;
    static constexpr unsigned GAP = 175;

    ShieldVector shields;

    sf::RenderWindow &window;

public:
    ShieldWall(sf::RenderWindow &window, Textures &textures, const unsigned screenw);
    ~ShieldWall();

    void reset();

    unsigned getY() const { return this->Y; }

    void handleCollisions(PlayerLaser &laser, Lasers &invader_lasers, InvaderFormation &invaders, Explosions &explosions);

    void draw();

};

#endif
