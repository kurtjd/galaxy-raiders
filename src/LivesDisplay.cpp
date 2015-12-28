#include <sstream>
#include "../inc/LivesDisplay.hpp"
#include "../inc/game.hpp"

void LivesDisplay::reset()
{
    // First clear
    for (auto& cannon : this->cannons)
        delete cannon;
    this->cannons.clear();

    this->lives = this->LIVES_START;

    // Subtract 1 from lives because the last life is the player's cannon.
    for (unsigned i = 0; i < (this->lives - 1); ++i)
    {
        sf::Sprite *sprite = new sf::Sprite;
        sprite->setTexture(this->textures.CORECANNON);
        sprite->setPosition(this->X + 75 + (i * 55), this->Y);
        this->cannons.push_back(sprite);
    }
}

LivesDisplay::LivesDisplay(Textures &textures): lives(LIVES_START), textures(textures)
{
    this->reset(); 
}

LivesDisplay::~LivesDisplay()
{
    for (auto& cannon : this->cannons)
        delete cannon;
    this->cannons.clear();
}

void LivesDisplay::removeLife()
{
    // Removes the last cannon from the vector.
    if (this->lives > 1)
    {
        delete this->cannons[this->lives - 2];
        this->cannons.pop_back();
    }

    // If player is out of lives it's game over!
    if (this->lives > 0)
        --this->lives;

    if (lives == 0)
        Globals::GAME_STATE = Globals::States::GAME_OVER;
}

void LivesDisplay::addLife()
{
    sf::Sprite *sprite = new sf::Sprite;
    sprite->setTexture(this->textures.CORECANNON);
    sprite->setPosition(this->X + 75 + ((this->lives - 1) * 55), this->Y);
    this->cannons.push_back(sprite);

    ++this->lives;
}

void LivesDisplay::setLives(const unsigned num)
{
    while (this->lives > num)
        this->removeLife();
}

void LivesDisplay::draw(sf::RenderWindow &window)
{
    std::ostringstream lives_left;
    lives_left << this->lives;

    // Draw number of lives left.
    Game::draw_text(window, lives_left.str(), this->X + 30, this->Y + 2); 

    Game::draw_text(window, "C R E D I T    0 0", this->X + 550, this->Y + 2); 

    // Draw cannon representing each life.
    for (auto& cannon : this->cannons)
        window.draw(*cannon);
}
