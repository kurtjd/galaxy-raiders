#include "../inc/InvaderLaser.hpp"

InvaderLaser::InvaderLaser(const LaserType type, const int speed, const unsigned shield_dmg): TYPE(type), SPEED(speed), SHIELD_DMG(shield_dmg), hit(false)
{
    // Subclass constructor does the real work.
    // This mainly just initializes members.
}

void InvaderLaser::remove()
{
    this->hit = true;
}
