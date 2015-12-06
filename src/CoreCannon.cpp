#include <iostream>
#include <SFML/Graphics.hpp>
#include "CoreCannon.hpp"

CoreCannon::CoreCannon(sf::Image &spritesheet, int startx): spritesheet(spritesheet)
{
    this->alive_txtr.loadFromImage(spritesheet, sf::IntRect(492, 40, 48, 30));
    this->sprite.setTexture(this->alive_txtr);
    this->sprite.setPosition(startx, 623);

    // Put the point of origin in center of cannon.
    this->sprite.setOrigin(this->alive_txtr.getSize().x / 2, this->alive_txtr.getSize().y / 2);
}

void CoreCannon::move(int dir)
{
    this->sprite.move(this->SPEED * dir, 0);
}
