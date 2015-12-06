#ifndef PLAYERcannon_H
#define PLAYERcannon_H

#include <SFML/Graphics.hpp>

class CoreCannon
{
private:
    static const int SPEED = 5; // Movement speed of cannon

    sf::Image spritesheet;
    sf::Texture alive_txtr;
    sf::Texture dead_txtr;
    sf::Sprite sprite;

public:
    CoreCannon(sf::Image &spritesheet, int startx);
    void move(int dir);
    sf::Sprite& getSprite(){ return this->sprite; }
    unsigned getX(){ return this->sprite.getPosition().x; }
    unsigned getWidth(){ return this->getSprite().getGlobalBounds().width; }

};

#endif
