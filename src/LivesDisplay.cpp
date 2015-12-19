#include "../inc/LivesDisplay.hpp"
#include "../inc/game.hpp"

LivesDisplay::LivesDisplay(Textures &textures): lives(LIVES_START)
{
    // Subtract 1 from LIVES_START because the last life is the player's cannon.
    for (unsigned i = 0; i < (this->LIVES_START - 1); ++i)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(textures.CORECANNON);
        sprite->setPosition(this->X + 75 + (i * 55), this->Y);
        this->cannons.push_back(sprite);
    }
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
