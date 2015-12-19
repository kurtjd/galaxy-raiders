#ifndef PLAYERcannon_H
#define PLAYERcannon_H

#include <SFML/Graphics.hpp>
#include "Textures.hpp"

/* The player's ship. */

class CoreCannon
{
private:
    static constexpr unsigned Y_POS = 623;
    static constexpr int SPEED = 5; // Movement speed of cannon

    sf::Sprite sprite;

public:
    CoreCannon(Textures &textures, const int startx);
    void move(const int dir);
    const sf::Sprite& getSprite() const { return this->sprite; }
    unsigned getX() const { return this->sprite.getPosition().x; }
    unsigned getWidth() const { return this->getSprite().getGlobalBounds().width; }

};

#endif
