#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <SFML/Graphics.hpp>

class PlayerShip
{
private:
    static const int SPEED = 5; // Movement speed of ship

    sf::Image spritesheet;
    
    // The sprite of the ship as it is alive (not exploding)
    sf::Texture alive_txtr;
    sf::Sprite alive_sprite;

    // The sprite of the ship as it is dead (exploding)
    sf::Texture dead_txtr;
    sf::Sprite dead_sprite;

public:
    PlayerShip(sf::Image &spritesheet, int startx);
    void move(int dir);
    sf::Sprite& getAliveSprite(){ return this->alive_sprite; }
    unsigned getX(){ return this->alive_sprite.getPosition().x; }
    unsigned getWidth(){ return this->getAliveSprite().getGlobalBounds().width; }

};

#endif
