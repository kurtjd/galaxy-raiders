#ifndef PLAYERcannon_H
#define PLAYERcannon_H

#include <SFML/Graphics.hpp>

/* The player's ship. */

class CoreCannon
{
private:
    static constexpr unsigned ALIVE_TXTR_X_START = 492;
    static constexpr unsigned ALIVE_TXTR_Y_START = 40;
    static constexpr unsigned ALIVE_TXTR_WIDTH = 48;
    static constexpr unsigned ALIVE_TXTR_HEIGHT = 30;

    static constexpr unsigned Y_POS = 623;

    static constexpr int SPEED = 5; // Movement speed of cannon

    sf::Image spritesheet;
    sf::Texture alive_txtr;
    sf::Texture dead_txtr;
    sf::Sprite sprite;

    const unsigned SCREENW;

public:
    CoreCannon(const sf::Image &spritesheet, const unsigned screenw, const int startx);
    void move(const int dir);
    const sf::Sprite& getSprite() const { return this->sprite; }
    unsigned getX() const { return this->sprite.getPosition().x; }
    unsigned getWidth() const { return this->getSprite().getGlobalBounds().width; }

};

#endif
