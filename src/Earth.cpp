#include <SFML/Graphics.hpp>
#include "Earth.hpp"

Earth::Earth(unsigned screenw)
{
    this->shape = sf::RectangleShape(sf::Vector2f(screenw, 2));
    this->shape.setPosition(0, 680);
    this->shape.setFillColor(sf::Color::Green);
}
