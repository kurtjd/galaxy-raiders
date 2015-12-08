#ifndef SHIELD_H
#define SHIELD_H

#include <SFML/Graphics.hpp>
#include "PlayerLaser.hpp"

class Shield
{
private:
    static const unsigned TXTR_X_START = 562;
    static const unsigned TXTR_Y_START = 13;
    static const unsigned TXTR_WIDTH = 80;
    static const unsigned TXTR_HEIGHT = 59;

    static const unsigned Y_POS = 520;

    static const int IMPACT_SIZE = 10; // Size of impact crater from laser.

    // The sprite of the shield.
    sf::Image &spritesheet;
    sf::Texture texture;
    sf::Sprite sprite;

    // Image made from texture for pixel collision
    sf::Image img;

public:
    Shield(sf::Image &spritesheet, int xpos);
    sf::Sprite& getSprite(){ return this->sprite; }

    // Checks for collisions with lasers
    bool checkCollide(PlayerLaser &laser);

    // Add splash damage to shield
    void damageShield(int x, int y);

};

#endif
