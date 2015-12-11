#include <cmath>
#include <SFML/Graphics.hpp>
#include "PlayerLaser.hpp"

PlayerLaser::PlayerLaser(): is_shooting(false)
{
    // Create player laser (there is only ever 1 player laser on screen at a time)
    this->laser = sf::RectangleShape(sf::Vector2f(this->WIDTH, this->HEIGHT));
    this->laser.setPosition(999, 999); // Position it off screen until shot
    this->laser.setFillColor(sf::Color::White);
    this->laser.setOrigin(round(this->WIDTH / 2), this->HEIGHT); // Make the origin bottom of laser
}

void PlayerLaser::shoot(unsigned startx, unsigned starty)
{
    // If laser is shooting, don't try to shoot again
    if (!this->is_shooting)
    {
        this->laser.setPosition(startx, starty);
        this->is_shooting = true;
    }
}

void PlayerLaser::move()
{
    // This will probably get called every frame, so don't move unless actually shooting
    if (!this->is_shooting)
        return;

    this->laser.move(0, this->SPEED * -1);

    // Player can shoot again when laser leaves screen
    if (this->laser.getPosition().y < 0)
        this->stop();
}

void PlayerLaser::stop()
{
    this->is_shooting = false;

    // Do this so the laser isn't sitting there waiting to be collided with.
    this->laser.setPosition(999, 999);
}
