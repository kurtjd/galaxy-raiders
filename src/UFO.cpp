#include "../inc/UFO.hpp"
#include "../inc/globals.hpp"
#include "../inc/misc.hpp"

bool UFO::toAppearOrNah()
{
    return Misc::random(1, this->APPEAR_CHANCE) == 1;
}

void UFO::appear()
{
    this->on_screen = true;
    this->sprite.setPosition(0 + 10, this->Y);
}

UFO::UFO(sf::Image &spritesheet): SCORES({50, 100, 150}), spritesheet(spritesheet), on_screen(false)
{
    this->alive_txtr.loadFromImage(this->spritesheet, sf::IntRect(this->ALIVE_TXTR_X, this->ALIVE_TXTR_Y, this->ALIVE_TXTR_WIDTH, this->ALIVE_TXTR_HEIGHT));

    this->dead_txtr.loadFromImage(this->spritesheet, sf::IntRect(this->DEAD_TXTR_X, this->DEAD_TXTR_Y, this->DEAD_TXTR_WIDTH, this->DEAD_TXTR_HEIGHT));

    this->sprite.setTexture(this->alive_txtr);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().width / 2);

    // Sprite image is a little large
    this->sprite.scale(0.6, 0.6);
}

void UFO::move()
{
    this->sprite.move(this->SPEED, 0);

    if (this->sprite.getPosition().x > Globals::SCREEN_WIDTH)
    {
        this->on_screen = false;
        this->sprite.setPosition(999, 999);
    }
}

void UFO::update()
{
    if (!this->on_screen && this->toAppearOrNah())
        this->appear();
    else if (this->on_screen)
        this->move();
}

void UFO::draw(sf::RenderWindow &window)
{
    if (this->on_screen)
        window.draw(this->sprite);
}
