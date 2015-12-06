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
    sf::Sprite shield_sprite;

    // Image made from texture for pixel collision
    sf::Image img;

public:
    Shield(sf::Image &spritesheet, int xpos);
    sf::Sprite& getSprite(){ return this->shield_sprite; }

    // Checks for collisions with lasers
    bool checkCollide(PlayerLaser &laser);

};

#endif
