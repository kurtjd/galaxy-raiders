#include "../inc/LivesDisplay.hpp"
#include "../inc/game.hpp"

void LivesDisplay::initCannons()
{
    // Subtract 1 from LIVES_START because the last life is the player's cannon.
    for (unsigned i = 0; i < (this->LIVES_START - 1); ++i)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(this->cannon_txtr);
        sprite->setPosition(this->X + 75 + (i * 55), this->Y);
        this->cannons.push_back(sprite);
    }
}

LivesDisplay::LivesDisplay(sf::Image &spritesheet): spritesheet(spritesheet), lives(LIVES_START)
{
    this->cannon_txtr.loadFromImage(spritesheet, sf::IntRect(this->CANNON_TXTR_X_START, this->CANNON_TXTR_Y_START, this->CANNON_TXTR_WIDTH, this->CANNON_TXTR_HEIGHT));

    this->initCannons();
}

LivesDisplay::~LivesDisplay()
{
    for (auto& cannon : this->cannons)
        delete cannon;
    this->cannons.clear();
}

void LivesDisplay::draw(sf::RenderWindow &window)
{
    // Draw number of lives left.
    Game::draw_text(window, "3", this->X + 30, this->Y + 2); 

    Game::draw_text(window, "C R E D I T    0 0", this->X + 550, this->Y + 2); 

    // Draw cannon representing each life.
    for (auto& cannon : this->cannons)
        window.draw(*cannon);
}
