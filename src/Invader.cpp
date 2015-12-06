#include <SFML/Graphics.hpp>
#include "Invader.hpp"

void Invader::setTextures(sf::IntRect frame1, sf::IntRect frame2)
{
    this->frame1_txtr.loadFromImage(this->spritesheet, frame1);
    this->frame2_txtr.loadFromImage(this->spritesheet, frame2);
}

Invader::Invader(sf::Image &spritesheet, InvaderType type): spritesheet(spritesheet), type(type), move_dir(1), is_dead(false), frame_on(1)
{
    sf::IntRect frame1_rect;
    sf::IntRect frame2_rect;

    // Load different textures and set different score values based on type of Invader
    switch (this->type)
    {
    case Invader::LARGE:
        frame1_rect = sf::IntRect(257, 35, 45, 30);
        frame2_rect = sf::IntRect(315, 35, 45, 30);
        this->score_value = 10;
        break;
    
    case Invader::MEDIUM:
        frame1_rect = sf::IntRect(126, 35, 41, 30);
        frame2_rect = sf::IntRect(186, 35, 45, 30);
        this->score_value = 20;
        break;
    
    case Invader::SMALL:
        frame1_rect = sf::IntRect(6, 35, 30, 30);
        frame2_rect = sf::IntRect(64, 35, 30, 30);
        this->score_value = 30;
        break;

    default:
        break;
    }

    this->setTextures(frame1_rect, frame2_rect);
    this->sprite.setTexture(this->frame1_txtr);
    
    // Put the point of origin in center of invader.
    this->sprite.setOrigin(this->frame1_txtr.getSize().x / 2, this->frame1_txtr.getSize().y / 2);
}

void Invader::die()
{
    this->is_dead = true;
}

void Invader::move()
{
    this->sprite.move(this->SPEED * this->move_dir, 0);

    if (this->frame_on == 1)
    {
        this->sprite.setTexture(this->frame2_txtr);
        this->frame_on = 2;
    }
    else
    {
        this->sprite.setTexture(this->frame1_txtr);
        this->frame_on = 1;
    }
}

void Invader::dropDown()
{
    // 35 is height of all Invaders
    this->sprite.move(0, 35);
}

void Invader::reverseDir()
{
    if (this->move_dir == 1)
        this->move_dir = -1;
    else if (this->move_dir == -1)
        this->move_dir = 1;
}

bool Invader::checkHitEdge(int screenw)
{
    if (this->isDead())
        return false;

    int x = this->sprite.getPosition().x;
    int half_width = (this->sprite.getTexture()->getSize().x) / 2;

    if ((x >= (screenw - half_width - 10) && this->move_dir == 1) || (x <= (half_width + 10) && this->move_dir == -1))
        return true;

    return false;
}
