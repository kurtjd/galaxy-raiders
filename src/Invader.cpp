#include "../inc/Invader.hpp"

void Invader::flipFrame()
{
    if (this->frame_on == 1)
    {
        this->sprite.setTexture(*(this->frame2_txtr), true);
        this->frame_on = 2;
    }
    else
    {
        this->sprite.setTexture(*(this->frame1_txtr), true);
        this->frame_on = 1;
    }
}

Invader::Invader(Textures &textures, const InvaderType type): type(type), move_dir(1), is_dead(false), frame_on(1), death_tick(0)
{
    // Load different textures and set different score values based on type of Invader
    switch (this->type)
    {
    case Invader::LARGE:
        this->frame1_txtr = &(textures.LARGE_INV_1);
        this->frame2_txtr = &(textures.LARGE_INV_2);
        this->score_value = 10;
        break;
    
    case Invader::MEDIUM:
        this->frame1_txtr = &(textures.MEDIUM_INV_1);
        this->frame2_txtr = &(textures.MEDIUM_INV_2);
        this->score_value = 20;
        break;
    
    case Invader::SMALL:
        this->frame1_txtr = &(textures.SMALL_INV_1);
        this->frame2_txtr = &(textures.SMALL_INV_2);
        this->score_value = 30;
        break;

    default:
        break;
    }

    this->frame3_txtr = &(textures.INVADER_DEATH);
    this->sprite.setTexture(*(this->frame1_txtr), true);
    
    // Put the point of origin in center of invader.
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().width / 2);
}

void Invader::die()
{
    this->sprite.setTexture(*(this->frame3_txtr), true);
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

void Invader::dropDown(const unsigned shield_line)
{
    if (this->isDead())
        return;

    this->sprite.move(0, this->HEIGHT);
    this->flipFrame();

    if (this->sprite.getPosition().y >= shield_line)
        this->sprite.setColor(sf::Color::Green);
}

void Invader::reverseDir()
{
    this->move_dir *= -1;
}

bool Invader::checkHitEdge(const int screenw)
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
