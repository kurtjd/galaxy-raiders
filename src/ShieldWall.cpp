#include "../inc/ShieldWall.hpp"

ShieldWall::ShieldWall(sf::RenderWindow &window, sf::Image &spritesheet, unsigned screenw): window(window), spritesheet(spritesheet)
{
    // This loop creates 4 shields across the screen.
    // -5 is to stop part of 5th shield from drawing at edge
    for (unsigned i = this->STARTX; i < screenw - 5; i += this->GAP)
        this->shields.push_back(new Shield(spritesheet, i));
}

ShieldWall::~ShieldWall()
{
    for (auto& shield : shields)
        delete shield;
    this->shields.clear();
}

void ShieldWall::handleCollisions(PlayerLaser &laser, Lasers &invader_lasers)
{
    for (auto& shield : shields)
        shield->handleCollide(laser, invader_lasers);
}

void ShieldWall::draw()
{
    for (auto& shield : shields)
        this->window.draw(shield->getSprite());
}
