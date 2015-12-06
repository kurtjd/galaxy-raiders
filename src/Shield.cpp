#include <SFML/Graphics.hpp>
#include "Shield.hpp"
#include <iostream>

Shield::Shield(sf::Image &spritesheet, int xpos): spritesheet(spritesheet)
{
    this->shield_txtr.loadFromImage(spritesheet, sf::IntRect(562, 13, 80, 59));
    this->shield_sprite.setTexture(this->shield_txtr);
    this->shield_sprite.setPosition(xpos, 520);
    this->img = shield_txtr.copyToImage();
}

bool Shield::checkCollide(PlayerLaser &laser)
{
    unsigned xpos = this->shield_sprite.getPosition().x;
    unsigned ypos = this->shield_sprite.getPosition().y;
    unsigned width = this->shield_sprite.getGlobalBounds().width;
    unsigned height = this->shield_sprite.getGlobalBounds().height;

    for (unsigned x = xpos; x < (xpos + width); ++x)
    {
        for (unsigned y = ypos; y < (ypos + height); ++y)
        {
            sf::Color pixel = this->img.getPixel(x, y);
            if (laser.getShape().getGlobalBounds().contains(x, y) && pixel.r != 0 && pixel.g != 0 && pixel.b != 0)
                return true;
        }
    }

    return false;
}
