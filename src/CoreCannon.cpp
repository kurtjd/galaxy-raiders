#include "../inc/globals.hpp"
#include "../inc/CoreCannon.hpp"

CoreCannon::CoreCannon(Textures &textures, const int startx)
{
    this->sprite.setTexture(textures.CORECANNON);
    this->sprite.setPosition(startx, this->Y_POS);

    // Put the point of origin in center of cannon.
    this->sprite.setOrigin(this->sprite.getTexture()->getSize().x / 2, this->sprite.getTexture()->getSize().y / 2);
}

void CoreCannon::move(const int dir)
{
    // +/- 10 because it stops the cannon from going slightly off screen
    if ((dir == 1 && (this->getX() < (Globals::SCREEN_WIDTH - (this->getWidth() / 2) - 10)))
        || (dir == -1 && (this->getX() > (0 + (this->getWidth() / 2) + 10))))
        this->sprite.move(this->SPEED * dir, 0);
}
