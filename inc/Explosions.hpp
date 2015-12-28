#ifndef EXPLOSIONS_H
#define EXPLOSIONS_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Textures.hpp"

/* HANDLED BY EXPLOSIONS CLASS */
class Explosion
{
private:
    static constexpr unsigned SHOW_TICK_START = 20;

    sf::Sprite sprite;
    unsigned show_tick;
    bool showing;

public:
    Explosion(Textures &textures, sf::Color color, const unsigned x, const unsigned y);
    bool isShowing() const { return this->showing; }

    void update();
    void draw(sf::RenderWindow &window);

};




class Explosions
{
private:
    std::vector<Explosion*> explosions;
    Textures &textures;

public:
    Explosions(Textures &textures);
    ~Explosions();

    void reset();

    void update();

    void draw(sf::RenderWindow &window);

    void newExplosion(sf::Color color, const unsigned x, const unsigned y);

};
#endif
