#ifndef PLAYERcannon_H
#define PLAYERcannon_H

#include <SFML/Graphics.hpp>

/* The player's ship. */

class CoreCannon
{
private:
    static const unsigned ALIVE_TXTR_X_START = 492;
    static const unsigned ALIVE_TXTR_Y_START = 40;
    static const unsigned ALIVE_TXTR_WIDTH = 48;
    static const unsigned ALIVE_TXTR_HEIGHT = 30;

    static const unsigned Y_POS = 623;

    static const int SPEED = 5; // Movement speed of cannon

    sf::Image spritesheet;
    sf::Texture alive_txtr;
    sf::Texture dead_txtr;
    sf::Sprite sprite;

    unsigned screenw;

public:
    CoreCannon(sf::Image &spritesheet, unsigned screenw, int startx);
    void move(int dir);
    sf::Sprite& getSprite(){ return this->sprite; }
    unsigned getX(){ return this->sprite.getPosition().x; }
    unsigned getWidth(){ return this->getSprite().getGlobalBounds().width; }

};

#endif
