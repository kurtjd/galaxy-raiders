#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayerShip.hpp"

PlayerShip::PlayerShip(sf::Image &spritesheet, int startx): spritesheet(spritesheet)
{
    this->alive_txtr.loadFromImage(spritesheet, sf::IntRect(492, 40, 48, 30));
    this->alive_sprite.setTexture(this->alive_txtr);
    this->alive_sprite.setPosition(startx, 623);

    // Put the point of origin in center of ship.
    this->alive_sprite.setOrigin(this->alive_txtr.getSize().x / 2, this->alive_txtr.getSize().y / 2);
}

void PlayerShip::move(int dir)
{
    this->alive_sprite.move(this->SPEED * dir, 0);
}
