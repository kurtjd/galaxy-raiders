#include "../inc/InvaderLaser.hpp"

InvaderLaser::InvaderLaser(sf::Image &spritesheet, LaserType type, unsigned x, unsigned y): spritesheet(spritesheet), type(type), hit(false)
{
    sf::IntRect txtr_rect;

    switch(this->type)
    {
    case InvaderLaser::NORMAL:
        txtr_rect = sf::IntRect(512, 108, 12, 22);
        this->shield_dmg = 10;
        break;

    case InvaderLaser::POWERED:
        //txtr_rect = sf::IntRect();
        this->shield_dmg = 15;
        break;

    default:
        break;
    }

    this->txtr.loadFromImage(this->spritesheet, txtr_rect);
    this->sprite.setTexture(this->txtr, true);
    this->sprite.setScale(0.8, 0.8);
    this->sprite.setRotation(180);
    
    this->sprite.setPosition(x, y);
}

void InvaderLaser::remove()
{
    this->hit = true;
}

void InvaderLaser::move()
{
    this->sprite.move(0, this->SPEED);
}
