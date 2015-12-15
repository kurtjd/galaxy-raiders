#include "../inc/CoreCannon.hpp"

CoreCannon::CoreCannon(const sf::Image &spritesheet, const unsigned screenw, const int startx): spritesheet(spritesheet), SCREENW(screenw)
{
    this->alive_txtr.loadFromImage(spritesheet, sf::IntRect(this->ALIVE_TXTR_X_START, this->ALIVE_TXTR_Y_START, this->ALIVE_TXTR_WIDTH, this->ALIVE_TXTR_HEIGHT));
    this->sprite.setTexture(this->alive_txtr);
    this->sprite.setPosition(startx, this->Y_POS);

    // Put the point of origin in center of cannon.
    this->sprite.setOrigin(this->alive_txtr.getSize().x / 2, this->alive_txtr.getSize().y / 2);
}

void CoreCannon::move(const int dir)
{
    // +/- 10 because it stops the cannon from going slightly off screen
    if ((dir == 1 && (this->getX() < (this->SCREENW - (this->getWidth() / 2) - 10)))
        || (dir == -1 && (this->getX() > (0 + (this->getWidth() / 2) + 10))))
        this->sprite.move(this->SPEED * dir, 0);
}
