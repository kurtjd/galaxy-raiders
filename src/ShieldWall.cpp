#include <SFML/Graphics.hpp>
#include "ShieldWall.hpp"

ShieldWall::ShieldWall(sf::RenderWindow &window, sf::Image &spritesheet, unsigned screenw): window(window), spritesheet(spritesheet)
{
    // This loop creates 4 shields across the screen.
    // -5 is to stop part of 5th shield from drawing at edge
    for (unsigned i = this->STARTX; i < screenw - 5; i += this->GAP)
        this->shields.push_back(new Shield(spritesheet, i));
}

ShieldWall::~ShieldWall()
{
    for (unsigned i = 0; i < this->shields.size(); ++i)
        delete this->shields[i];

    this->shields.clear();
}

void ShieldWall::draw()
{
    for (unsigned i = 0; i < this->shields.size(); ++i)
        this->window.draw(this->shields[i]->getSprite());
}
