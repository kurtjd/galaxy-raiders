#include "../inc/ShieldWall.hpp"

ShieldWall::ShieldWall(sf::RenderWindow &window, Textures &textures, const unsigned screenw): window(window)
{
    // This loop creates 4 shields across the screen.
    // -5 is to stop part of 5th shield from drawing at edge
    for (unsigned i = this->STARTX; i < screenw - 5; i += this->GAP)
        this->shields.push_back(new Shield(textures, i, this->Y));
}

ShieldWall::~ShieldWall()
{
    for (auto& shield : shields)
        delete shield;
    this->shields.clear();
}

void ShieldWall::reset()
{
    for (auto& shield : shields)
        shield->reset();
}

void ShieldWall::handleCollisions(PlayerLaser &laser, Lasers &invader_lasers, InvaderFormation &invaders, Explosions &explosions)
{
    for (auto& shield : shields)
    {
        shield->handleCollide(laser, invader_lasers, explosions);
        shield->handleCollideInvaders(invaders);
    }
}

void ShieldWall::draw()
{
    for (auto& shield : shields)
        this->window.draw(shield->getSprite());
}
