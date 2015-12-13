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
    // Where the first shield starts and the gap between subsequent shields
    static const unsigned STARTX = 97;
    static const unsigned GAP = 175;

    ShieldVector shields;

    sf::RenderWindow &window;
    sf::Image &spritesheet;

public:
    ShieldWall(sf::RenderWindow &window, sf::Image &spritesheet, unsigned screenw);
    ~ShieldWall();

    void handleCollisions(PlayerLaser &laser, Lasers &invader_lasers);

    void draw();

};

#endif
