#include <SFML/Graphics.hpp>
#include "InvaderFormation.hpp"

InvaderFormation::InvaderFormation(sf::RenderWindow &window, sf::Image &spritesheet, SoundFx &death_snd, unsigned screenw): window(window), spritesheet(spritesheet), death_snd(death_snd), screenw(screenw), move_tick(0), move_tick_max(MOVE_TICK_MAX_START), move_tick_change(MOVE_TICK_CHANGE_START)
{
    // Vector for each row in the formation
    InvaderRow small_invaders;
    InvaderRow medium_invaders1;
    InvaderRow medium_invaders2;
    InvaderRow large_invaders1;
    InvaderRow large_invaders2;

    for (unsigned i = 1; i <= this->ROWS; ++i)
    {
        small_invaders.push_back(new Invader(this->spritesheet, Invader::SMALL));
        medium_invaders1.push_back(new Invader(this->spritesheet, Invader::MEDIUM));
        medium_invaders2.push_back(new Invader(this->spritesheet, Invader::MEDIUM));
        large_invaders1.push_back(new Invader(this->spritesheet, Invader::LARGE));
        large_invaders2.push_back(new Invader(this->spritesheet, Invader::LARGE));
    }

    // Now add each row to the main vector
    this->invaders.push_back(small_invaders);
    this->invaders.push_back(medium_invaders1);
    this->invaders.push_back(medium_invaders2);
    this->invaders.push_back(large_invaders1);
    this->invaders.push_back(large_invaders2);

    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
            this->invaders[i][j]->getSprite().setPosition(this->STARTX + (j * this->XGAP), this->STARTY + (i * this->YGAP));
    }
}

InvaderFormation::~InvaderFormation()
{
    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
            delete this->invaders[i][j];

        this->invaders[i].clear();
    }

    this->invaders.clear();
}

bool InvaderFormation::move()
{
    ++this->move_tick;
    if (this->move_tick == this->move_tick_max)
    {
        bool hit_edge = false;
        for (unsigned i = 0; i < this->invaders.size(); ++i)
        {
            for (unsigned j = 0; j < this->invaders[i].size(); ++j)
            {
                Invader *invader = this->invaders[i][j];

                invader->move();
                if (invader->checkHitEdge(this->screenw))
                    hit_edge = true;
            }
        }

        if (hit_edge)
            this->shift();

        this->move_tick = 0;

        return true;
    }

    return false;
}

void InvaderFormation::shift()
{
    // Slow down move tick change if max is getting
    // close to 0, and don't go any lower than 1 so they
    // don't stop moving.
    if (this->move_tick_max > 5)
        this->move_tick_max -= this->move_tick_change;
    else if (this->move_tick_max > 1)
        --this->move_tick_max;

    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
        {
            Invader *invader = this->invaders[i][j];
            invader->dropDown();
            invader->reverseDir();
        }
    }
}

void InvaderFormation::checkHit(PlayerLaser &laser)
{
    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
        {
            Invader *invader = this->invaders[i][j];
            if (!invader->isDead() && invader->getSprite().getGlobalBounds().intersects(laser.getShape().getGlobalBounds()))
            {
                invader->die();
                /*--this->move_tick_max; // Formation speeds up as they die
                if (this->move_tick >= this->move_tick_max)
                    this->move_tick = 0;*/

                this->death_snd.play();
                laser.stop();
            }
        }

    }
}

void InvaderFormation::draw()
{
    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
        {
            Invader *invader = this->invaders[i][j];
            if (!invader->isDead())
                this->window.draw(invader->getSprite());
        }
    }
}
