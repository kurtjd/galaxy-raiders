#include <SFML/Graphics.hpp>
#include "Shield.hpp"

Shield::Shield(sf::Image &spritesheet, int xpos): spritesheet(spritesheet), x(xpos)
{
    this->shield_txtr.loadFromImage(spritesheet, sf::IntRect(562, 13, 80, 59));
    this->shield_sprite.setTexture(this->shield_txtr);
    this->shield_sprite.setPosition(this->x, 500); // 500 is the y pos, which never changes.
}
