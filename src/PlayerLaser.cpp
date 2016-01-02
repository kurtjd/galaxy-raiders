#include <cmath>
#include "PlayerLaser.hpp"
#include "UFO.hpp"

PlayerLaser::PlayerLaser(SoundFx &shoot_snd): is_shooting(false), shoot_snd(shoot_snd)
{
    // Create player laser (there is only ever 1 player laser on screen at a time)
    this->laser = sf::RectangleShape(sf::Vector2f(this->WIDTH, this->HEIGHT));
    this->laser.setPosition(999, 999); // Position it off screen until shot
    this->laser.setFillColor(sf::Color::White);
    this->laser.setOrigin(round(this->WIDTH / 2), this->HEIGHT); // Make the origin bottom of laser
}

void PlayerLaser::shoot(const unsigned startx, const unsigned starty, UFO &ufo)
{
    // If laser is shooting, don't try to shoot again
    if (!this->is_shooting)
    {
        this->shoot_snd.play();
        this->laser.setPosition(startx, starty);
        ufo.incShotsFired();
        this->is_shooting = true;
    }
}

void PlayerLaser::move(Explosions &explosions)
{
    // This will probably get called every frame, so don't move unless actually shooting
    if (!this->is_shooting)
        return;

    this->laser.move(0, this->SPEED * -1);

    // Player can shoot again when laser leaves screen
    if (this->laser.getPosition().y < 100)
    {
        explosions.newExplosion(sf::Color::Red, this->getShape().getPosition().x, this->getShape().getPosition().y);
        this->stop();
    }
}

void PlayerLaser::stop()
{
    this->is_shooting = false;

    // Do this so the laser isn't sitting there waiting to be collided with.
    this->laser.setPosition(999, 999);
}
