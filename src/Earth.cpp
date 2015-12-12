#include <SFML/Graphics.hpp>
#include "../inc/Earth.hpp"

Earth::Earth(unsigned screenw)
{
    this->shape = sf::RectangleShape(sf::Vector2f(screenw, this->HEIGHT));
    this->shape.setPosition(this->X, this->Y);
    this->shape.setFillColor(sf::Color::Green);
}
