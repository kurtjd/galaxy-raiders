#ifndef SHIELD_H
#define SHIELD_H

#include <SFML/Graphics.hpp>
#include "PlayerLaser.hpp"
#include "InvaderFormation.hpp"

/* The shields protection the player from incoming fire. */

class Shield
{
private:
    static constexpr unsigned TXTR_X_START = 562;
    static constexpr unsigned TXTR_Y_START = 13;
    static constexpr unsigned TXTR_WIDTH = 80;
    static constexpr unsigned TXTR_HEIGHT = 59;

    static constexpr unsigned Y_POS = 520;

    // The sprite of the shield.
    sf::Image &spritesheet;
    sf::Texture texture;
    sf::Sprite sprite;

    // Image made from texture for pixel collision
    sf::Image img;

public:
    Shield(sf::Image &spritesheet, const int xpos);
    sf::Sprite& getSprite(){ return this->sprite; }

    // Handles for collisions with lasers
    void handleCollide(PlayerLaser &player_laser, Lasers &invader_lasers);

    // Add splash damage to shield
    void damageShield(int x, int y, const int dmg);

};

#endif
