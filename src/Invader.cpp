#include <SFML/Graphics.hpp>
#include "Invader.hpp"

void Invader::setTextures(sf::IntRect frame1, sf::IntRect frame2)
{
    this->frame1_txtr.loadFromImage(this->spritesheet, frame1);
    this->frame2_txtr.loadFromImage(this->spritesheet, frame2);
}

Invader::Invader(sf::Image &spritesheet): spritesheet(spritesheet), move_dir(0)
{

}
