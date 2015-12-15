#include "../inc/Earth.hpp"

Earth::Earth(const unsigned screenw)
{
    this->shape = sf::RectangleShape(sf::Vector2f(screenw, this->HEIGHT));
    this->shape.setPosition(this->X, this->Y);
    this->shape.setFillColor(sf::Color::Green);
}
