#include <SFML/Graphics.hpp>
#include "PlayerBullet.hpp"

PlayerBullet::PlayerBullet(): is_shooting(false)
{
    // Create player bullet (there is only ever 1 player bullet on screen at a time)
    this->bullet = sf::RectangleShape(sf::Vector2f(3, 15));
    this->bullet.setPosition(999, 999); // Position it off screen until shot
    this->bullet.setFillColor(sf::Color::White);
    this->bullet.setOrigin(2, 15); // Make the origin bottom of bullet
}

void PlayerBullet::shoot(unsigned startx, unsigned starty)
{
    // If bullet is shooting, don't try to shoot again
    if (!this->is_shooting)
    {
        this->bullet.setPosition(startx, starty);
        this->is_shooting = true;
    }
}

void PlayerBullet::move()
{
    // This will probably get called every frame, so don't move unless actually shooting
    if (!this->is_shooting)
        return;

    this->bullet.move(0, this->SPEED * -1);

    // Player can shoot again when bullet leaves screen
    if (this->bullet.getPosition().y < 0)
        this->is_shooting = false;
}
