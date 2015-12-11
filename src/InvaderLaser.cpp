#include <SFML/Graphics.hpp>
#include "InvaderLaser.hpp"

InvaderLaser::InvaderLaser(sf::Image &spritesheet, LaserType type, unsigned x, unsigned y): spritesheet(spritesheet), type(type)
{
    sf::IntRect txtr_rect;

    switch(this->type)
    {
    case InvaderLaser::NORMAL:
        txtr_rect = sf::IntRect(512, 108, 12, 22);
        break;

    case InvaderLaser::POWERED:
        //txtr_rect = sf::IntRect();
        break;

    default:
        break;
    }

    this->txtr.loadFromImage(this->spritesheet, txtr_rect);
    this->sprite.setTexture(this->txtr, true);
    
    this->sprite.setPosition(x, y);
}
