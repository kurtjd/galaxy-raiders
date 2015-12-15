#include "../inc/InvaderLaser.hpp"

void InvaderLaser::createNormLaser(const unsigned x, const unsigned y)
{
    // TODO: Get rid of magic numbers.
    this->v_part = sf::RectangleShape(sf::Vector2f(2, 15));
    this->h_part = sf::RectangleShape(sf::Vector2f(12, 2));

    this->v_part.setFillColor(sf::Color::White);
    this->h_part.setFillColor(sf::Color::White);

    this->v_part.setPosition(x + 5, y);
    this->h_part.setPosition(x, y);
}

bool InvaderLaser::checkCollideNormLaser(const unsigned x, const unsigned y) const
{
    if (this->v_part.getGlobalBounds().contains(x, y) || this->h_part.getGlobalBounds().contains(x, y))
        return true;

    return false;
}

void InvaderLaser::moveNormLaser()
{
    this->v_part.move(0, this->SPEED);
    this->h_part.move(0, this->SPEED);
}

void InvaderLaser::drawNormLaser(sf::RenderWindow &window)
{
    window.draw(this->v_part);
    window.draw(this->h_part);
}

InvaderLaser::InvaderLaser(const LaserType type, const unsigned x, const unsigned y): type(type), hit(false)
{
    switch(this->type)
    {
    case InvaderLaser::NORMAL:
        this->createNormLaser(x, y);
        this->shield_dmg = 15;
        break;

    case InvaderLaser::POWERED:
        // TODO
        this->shield_dmg = 20;
        break;

    default:
        break;
    }
}

void InvaderLaser::remove()
{
    this->hit = true;
}

void InvaderLaser::move()
{
    switch(this->type)
    {
    case InvaderLaser::NORMAL:
        this->moveNormLaser();
        break;

    case InvaderLaser::POWERED:
        break;

    default:
        break;
    }
}

void InvaderLaser::draw(sf::RenderWindow &window)
{
    switch(this->type)
    {
    case InvaderLaser::NORMAL:
        this->drawNormLaser(window);
        break;

    case InvaderLaser::POWERED:
        break;

    default:
        break;
    }
}

bool InvaderLaser::checkCollide(const unsigned x, const unsigned y) const
{
    switch(this->type)
    {
    case InvaderLaser::NORMAL:
        return this->checkCollideNormLaser(x, y);
        break;

    case InvaderLaser::POWERED:
        break;

    default:
        break;
    }

    return false; // Shouldn't get here...
}
