#ifndef SHIELD_H
#define SHIELD_H

#include <SFML/Graphics.hpp>

class Shield
{
private:
    sf::Image spritesheet;
    int x; // Position of shield
    
    // The sprite of the shield.
    sf::Texture shield_txtr;
    sf::Sprite shield_sprite;

public:
    Shield(sf::Image &spritesheet, int xpos);
    sf::Sprite& getSprite(){ return this->shield_sprite; }

};

#endif
