#include <SFML/Graphics.hpp>
#include "Shield.hpp"
#include <iostream>

Shield::Shield(sf::Image &spritesheet, int xpos): spritesheet(spritesheet)
{
    this->shield_txtr.loadFromImage(spritesheet, sf::IntRect(562, 13, 80, 59));
    this->sprite.setTexture(this->shield_txtr);
    this->sprite.setPosition(xpos, 520);
    this->img = shield_txtr.copyToImage();
}

bool Shield::checkCollide(PlayerLaser &laser)
{
    unsigned xpos = this->sprite.getPosition().x;
    unsigned ypos = this->sprite.getPosition().y;
    unsigned width = this->sprite.getGlobalBounds().width;
    unsigned height = this->sprite.getGlobalBounds().height;

    for (unsigned x = xpos; x < (xpos + width); ++x)
    {
        for (unsigned y = ypos; y < (ypos + height); ++y)
        {
            // Subtract xpos and ypos because the Image uses its own local coordinates
            sf::Color pixel = this->img.getPixel(x - xpos, y - ypos);

            // Only true if hit green pixel
            if (laser.getShape().getGlobalBounds().contains(x, y) && pixel.g > 0)
            {
                // Eh, probably shouldn't have side-effect in bool method, but it's too easy
                this->damageShield(x - xpos, y - ypos);
                return true;
            }
        }
    }

    return false;
}

void Shield::damageShield(int x, int y)
{
    int oldx = x;
    int oldy = y;

    for (x -= 10; x < (oldx + 10); ++x)
    {
        if (x < 0 || x > this->img.getSize().x)
            continue;

        for (y -= 10; y < (oldy + 10); ++y)
        {
            if (y < 0 || y > this->img.getSize().y)
                continue;

            this->img.setPixel(x, y, sf::Color::Transparent);
        }
    }
    
    this->shield_txtr.update(img);
    this->sprite.setTexture(this->shield_txtr);
}
