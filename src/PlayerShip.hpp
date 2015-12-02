#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <SFML/Graphics.hpp>

class PlayerShip
{
private:
    sf::Image spritesheet;
    int x; // Ship's position on the screen
    
    // The sprite of the ship as it is alive (not exploding)
    sf::Texture alive_txtr;
    sf::Sprite alive_sprite;
    
    // The sprite of the ship as it is dead (exploding)
    sf::Texture dead_txtr;
    sf::Sprite dead_sprite;

public:
    PlayerShip(sf::Image &spritesheet, int startx);
    sf::Sprite& getAliveSprite(){ return this->alive_sprite; }

};

#endif
