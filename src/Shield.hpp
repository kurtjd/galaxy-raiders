#ifndef SHIELD_H
#define SHIELD_H

#include <SFML/Graphics.hpp>

class Shield
{
private:
    // The sprite of the shield.
    sf::Image spritesheet;
    sf::Texture shield_txtr;
    sf::Sprite shield_sprite;

public:
    Shield(sf::Image &spritesheet, int xpos);
    sf::Sprite& getSprite(){ return this->shield_sprite; }

};

#endif
