#include "../inc/InvaderFormation.hpp"

void InvaderFormation::incDeathTick()
{
    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
        {
            Invader *invader = this->invaders[i][j];
            if (invader->isExploding())
                invader->incDeathTick();
        }
    }
}

void InvaderFormation::playStepSound()
{
// Invaders make 4 sounds in a loop on each step
    switch (this->step_on)
    {
    case 1:
        this->step1.play();
        break;

    case 2:
        this->step2.play();
        break;

    case 3:
        this->step3.play();
        break;

    case 4:
        this->step4.play();
        break;

    default:
        break;
    }


    ++this->step_on;
    if (this->step_on > 4)
        this->step_on = 1;
}

InvaderFormation::InvaderFormation(sf::RenderWindow &window, sf::Image &spritesheet, unsigned screenw, SoundFx &death_snd, SoundFx &step1, SoundFx &step2, SoundFx &step3, SoundFx &step4): step1(step1), step2(step2), step3(step3), step4(step4), window(window), spritesheet(spritesheet), death_snd(death_snd), screenw(screenw), move_tick(0), move_tick_max(MOVE_TICK_MAX_START), move_tick_change(MOVE_TICK_CHANGE_START), step_on(1), num_killed(0), has_hit_edge(false)
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
    // Destroy Invaders
    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
            delete this->invaders[i][j];

        this->invaders[i].clear();
    }
    this->invaders.clear();

    // Destroy lasers
    for (unsigned i = 0; i < this->lasers.size(); ++i)
        delete this->lasers[i];
    this->lasers.clear();
}

bool InvaderFormation::move()
{
    this->incDeathTick(); // move() is called every frame so we put this here.
    ++this->move_tick;
    if (this->move_tick == this->move_tick_max)
    {
        if (this->has_hit_edge)
        {
            this->shift();
            this->has_hit_edge = false;
        }
        else
        {
            for (unsigned i = 0; i < this->invaders.size(); ++i)
            {
                for (unsigned j = 0; j < this->invaders[i].size(); ++j)
                {
                    Invader *invader = this->invaders[i][j];

                    invader->move();
                    if (invader->checkHitEdge(this->screenw))
                        this->has_hit_edge = true;
                }
            }
        }

        this->move_tick = 0;
        this->playStepSound();

        return true;
    }

    return false;
}

void InvaderFormation::shift()
{
    // Slow down move tick change if max is getting
    // close to 0, and don't go any lower than 1 so they
    // don't stop moving.
    if (this->move_tick_max > 20)
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

                // Formation speeds up for every 2 Invaders killed.
                ++this->num_killed;
                if (!(this->num_killed % 2) && this->move_tick_max > 1)
                {
                    --this->move_tick_max;
                    if (this->move_tick >= this->move_tick_max)
                        this->move_tick = this->move_tick_max - 1; // This is to keep the formation moving
                }

                this->death_snd.play();
                laser.stop();

                return; // Only 1 Invader can be hit at a time, so this saves time.
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
            if (!invader->isDead() || (invader->isDead() && invader->isExploding()))
                this->window.draw(invader->getSprite());
        }
    }
}
