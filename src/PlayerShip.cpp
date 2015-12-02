#include <SFML/Graphics.hpp>
#include "PlayerShip.hpp"

PlayerShip::PlayerShip(sf::Image &spritesheet, int startx): spritesheet(spritesheet), x(startx)
{
    this->alive_txtr.loadFromImage(spritesheet, sf::IntRect(492, 40, 48, 30));
    this->alive_sprite.setTexture(this->alive_txtr);
    this->alive_sprite.setPosition(this->x, 580);
}
