#include <SFML/Graphics.hpp>
#include "../inc/Invader.hpp"

void Invader::setTextures(sf::IntRect frame1, sf::IntRect frame2, sf::IntRect frame3)
{
    this->frame1_txtr.loadFromImage(this->spritesheet, frame1);
    this->frame2_txtr.loadFromImage(this->spritesheet, frame2);
    this->frame3_txtr.loadFromImage(this->spritesheet, frame3);
}

void Invader::flipFrame()
{
    if (this->frame_on == 1)
    {
        this->sprite.setTexture(this->frame2_txtr, true);
        this->frame_on = 2;
    }
    else
    {
        this->sprite.setTexture(this->frame1_txtr, true);
        this->frame_on = 1;
    }
}

Invader::Invader(sf::Image &spritesheet, InvaderType type): spritesheet(spritesheet), type(type), move_dir(1), is_dead(false), frame_on(1), death_tick(0)
{
    sf::IntRect frame1_rect;
    sf::IntRect frame2_rect;

    // Load different textures and set different score values based on type of Invader
    switch (this->type)
    {
    case Invader::LARGE:
        frame1_rect = sf::IntRect(257, 35, 45, this->TXTR_HEIGHT);
        frame2_rect = sf::IntRect(315, 35, 45, this->TXTR_HEIGHT);
        this->score_value = 10;
        break;
    
    case Invader::MEDIUM:
        frame1_rect = sf::IntRect(126, 35, 41, this->TXTR_HEIGHT);
        frame2_rect = sf::IntRect(186, 35, 45, this->TXTR_HEIGHT);
        this->score_value = 20;
        break;
    
    case Invader::SMALL:
        frame1_rect = sf::IntRect(6, 35, 30, this->TXTR_HEIGHT);
        frame2_rect = sf::IntRect(64, 35, 30, this->TXTR_HEIGHT);
        this->score_value = 30;
        break;

    default:
        break;
    }

    // Death frame (same for all types)
    sf::IntRect frame3_rect(555, 107, 48, 102);

    this->setTextures(frame1_rect, frame2_rect, frame3_rect);
    this->sprite.setTexture(this->frame1_txtr, true);
    
    // Put the point of origin in center of invader.
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().width / 2);
}

void Invader::die()
{
    this->sprite.setTexture(this->frame3_txtr, true);
    this->is_exploding = true;
    this->is_dead = true;
}

void Invader::move()
{
    if (this->isDead())
        return;

    this->sprite.move(this->SPEED * this->move_dir, 0);
    this->flipFrame();
}

void Invader::dropDown()
{
    if (this->isDead())
        return;

    this->sprite.move(0, this->TXTR_HEIGHT);
    this->flipFrame();
}

void Invader::reverseDir()
{
    this->move_dir *= -1;
}

bool Invader::checkHitEdge(int screenw)
{
    if (this->isDead())
        return false;

    int x = this->sprite.getPosition().x;
    int half_width = (this->sprite.getTexture()->getSize().x) / 2;

    // +/- 10 to stop from going slightly off screen
    if ((x >= (screenw - half_width - 10) && this->move_dir == 1) || (x <= (half_width + 10) && this->move_dir == -1))
        return true;

    return false;
}

void Invader::incDeathTick()
{
    ++this->death_tick;
    if (this->death_tick >= this->DEATH_TICK_MAX)
        this->is_exploding = false;
}
