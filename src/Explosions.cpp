#include "Explosions.hpp"

/* BEGIN EXPLOSION CLASS METHODS */
Explosion::Explosion(Textures &textures, sf::Color color, const unsigned x, const unsigned y): show_tick(SHOW_TICK_START), showing(true)
{
    this->sprite.setTexture(textures.EXPLOSION);

    this->sprite.setPosition(x, y);
    this->sprite.setColor(color);
}

void Explosion::update()
{
    --this->show_tick;

    if (this->show_tick == 0)
        this->showing = false;
}

void Explosion::draw(sf::RenderWindow &window)
{
    window.draw(this->sprite);
}




/* BEGIN EXPLOSIONS CLASS METHODS */
Explosions::Explosions(Textures &textures): textures(textures)
{

}

Explosions::~Explosions()
{
    this->reset(); 
}

void Explosions::reset()
{
    for (auto &explosion : this->explosions)
        delete explosion;
    explosions.clear();
}

void Explosions::update()
{
    for (unsigned i = 0; i < this->explosions.size(); ++i)
    {
        Explosion *explosion = this->explosions[i];

        explosion->update();

        // Delete explosions that have shown for long enough.
        if (!explosion->isShowing())
        {
            delete explosion;
            this->explosions.erase(this->explosions.begin() + i);
        }
    }
}

void Explosions::draw(sf::RenderWindow &window)
{
    for (auto &explosion : this->explosions)
        explosion->draw(window);
}

void Explosions::newExplosion(sf::Color color, const unsigned x, const unsigned y)
{
    this->explosions.push_back(new Explosion(this->textures, color, x, y));
}
