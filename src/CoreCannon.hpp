#ifndef PLAYERcannon_H
#define PLAYERcannon_H

#include <SFML/Graphics.hpp>

class CoreCannon
{
private:
    static const int SPEED = 5; // Movement speed of cannon

    sf::Image spritesheet;
    
    // The sprite of the cannon as it is alive (not exploding)
    sf::Texture alive_txtr;
    sf::Sprite alive_sprite;

    // The sprite of the cannon as it is dead (exploding)
    sf::Texture dead_txtr;
    sf::Sprite dead_sprite;

public:
    CoreCannon(sf::Image &spritesheet, int startx);
    void move(int dir);
    sf::Sprite& getAliveSprite(){ return this->alive_sprite; }
    unsigned getX(){ return this->alive_sprite.getPosition().x; }
    unsigned getWidth(){ return this->getAliveSprite().getGlobalBounds().width; }

};

#endif
