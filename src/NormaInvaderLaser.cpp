#include "../inc/NormalInvaderLaser.hpp"

NormalInvaderLaser::NormalInvaderLaser(const unsigned x, const unsigned y): InvaderLaser(LaserType::NORMAL, 5, 15)
{
    // TODO: Get rid of magic numbers.
    this->v_part = sf::RectangleShape(sf::Vector2f(2, 15));
    this->h_part = sf::RectangleShape(sf::Vector2f(12, 2));

    this->v_part.setFillColor(sf::Color::White);
    this->h_part.setFillColor(sf::Color::White);

    this->v_part.setPosition(x + 5, y);
    this->h_part.setPosition(x, y);
}

void NormalInvaderLaser::move()
{
    this->v_part.move(0, this->SPEED);
    this->h_part.move(0, this->SPEED);
}

void NormalInvaderLaser::draw(sf::RenderWindow &window)
{
    window.draw(this->v_part);
    window.draw(this->h_part);
}

bool NormalInvaderLaser::checkCollide(const unsigned x, const unsigned y) const
{
    if (this->v_part.getGlobalBounds().contains(x, y) || this->h_part.getGlobalBounds().contains(x, y))
        return true;

    return false;
}

bool NormalInvaderLaser::checkCollide(const sf::FloatRect rect) const
{
    if (rect.intersects(this->v_part.getGlobalBounds()) || rect.intersects(this->h_part.getGlobalBounds()))
        return true;

    return false;
}
