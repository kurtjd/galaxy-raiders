#include "../inc/InvaderLaser.hpp"

InvaderLaser::InvaderLaser(sf::Image &spritesheet, const LaserType type, const unsigned x, const unsigned y): spritesheet(spritesheet), type(type), hit(false)
{
    sf::IntRect txtr_rect;

    switch(this->type)
    {
    case InvaderLaser::NORMAL:
        txtr_rect = sf::IntRect(512, 108, 12, 22);
        this->shield_dmg = 15;
        break;

    case InvaderLaser::POWERED:
        // TODO
        //txtr_rect = sf::IntRect();
        this->shield_dmg = 20;
        break;

    default:
        break;
    }

    this->txtr.loadFromImage(this->spritesheet, txtr_rect);
    this->sprite.setTexture(this->txtr, true);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height);
    this->sprite.setScale(0.8, 0.8); // The actual image is a little large.
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
