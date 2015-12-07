#ifndef SHIELD_H
#define SHIELD_H

#include <SFML/Graphics.hpp>
#include "PlayerLaser.hpp"

class Shield
{
private:
    // The sprite of the shield.
    sf::Image &spritesheet;
    sf::Texture shield_txtr;
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
