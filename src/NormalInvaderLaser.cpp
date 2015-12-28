#include "../inc/NormalInvaderLaser.hpp"

void NormalInvaderLaser::moveHPart()
{
    unsigned h_part_y = this->h_part.getPosition().y;
    unsigned v_part_y = this->v_part.getPosition().y;

    if ((h_part_y >= (v_part_y + this->HEIGHT - this->THICKNESS)) && this->h_part_movedir == 1)
        this->h_part_movedir = -1;
    else if ((h_part_y <= (v_part_y)) && this->h_part_movedir == -1)
        this->h_part_movedir = 1;

    // If moving down, need to move slightly faster than the vert part.
    // Stays still if moving 'Up' (illusion created by vert part still moving down)
    if (this->h_part_movedir == 1)
        this->h_part.move(0, this->SPEED * this->h_part_moverate);
}

NormalInvaderLaser::NormalInvaderLaser(const unsigned x, const unsigned y, const unsigned shield_line, const bool will_hurt, Invader &owner): InvaderLaser(LaserType::NORMAL, 5, 15, shield_line, will_hurt, owner), h_part_movedir(1)
{
    this->v_part = sf::RectangleShape(sf::Vector2f(this->THICKNESS, this->HEIGHT));
    this->h_part = sf::RectangleShape(sf::Vector2f(this->WIDTH, this->THICKNESS));

    this->v_part.setFillColor(sf::Color::White);
    this->h_part.setFillColor(sf::Color::White);

    this->v_part.setPosition(x + ((this->WIDTH / 2) - 1), y);
    this->h_part.setPosition(x, y);
}

unsigned NormalInvaderLaser::getX() const
{
    return this->v_part.getPosition().x;
}

unsigned NormalInvaderLaser::getY() const
{
    return this->v_part.getPosition().y;
}

void NormalInvaderLaser::move()
{
    this->v_part.move(0, this->SPEED);
    this->moveHPart();

    // Change color to green once past the shields.
    if (this->v_part.getPosition().y >= this->SHIELD_LINE)
    {
        this->v_part.setFillColor(sf::Color::Green);
        this->h_part.setFillColor(sf::Color::Green);
    }
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
