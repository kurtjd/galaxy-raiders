#include "../inc/globals.hpp"
#include "../inc/misc.hpp"
#include "../inc/InvaderFormation.hpp"

void InvaderFormation::incDeathTick()
{
    for (auto& invader_row : this->invaders)
    {
        for (auto& invader : invader_row)
        {
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

void InvaderFormation::increaseFire(int amount)
{
   this->shot_chance -= amount;
   if (this->shot_chance < 10)
       shot_chance = 10;
}

bool InvaderFormation::toShootOrNah() const
{
    // Arbitrary number, there is 1/shot_chance of returning true.
    return Misc::random(1, this->shot_chance) == 1;
}

void InvaderFormation::shootLaser(unsigned x, unsigned y)
{
    InvaderLaser *laser;
    
    // Normal lasers have a slightly greater chance of being created.
    unsigned dice_roll = Misc::random(1, 10);
    if (dice_roll <= 6)
        laser = new NormalInvaderLaser(x, y, this->SHIELD_LINE);
    else
        laser = new PoweredInvaderLaser(x, y, this->SHIELD_LINE);

    this->lasers.push_back(laser);
}

void InvaderFormation::handleCollisions()
{
    for (unsigned i = 0; i < this->lasers.size(); ++i)
    {
        InvaderLaser *laser = this->lasers[i];
        if (laser->checkCollide(earth.getSprite().getGlobalBounds()))
        {
            earth.destroy(laser->getX());
            this->lasers.erase(this->lasers.begin() + i);
        }
    }
}

void InvaderFormation::shootLasers()
{
    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
        {
            Invader *invader = this->invaders[i][j];

            // Only shoot if Invader is alive and hits the jackpot.
            if (!invader->isDead() && this->toShootOrNah())
            {
                bool shoot = true;

                // Only shoot a laser if there is no Invader below the current Invader.
                for (unsigned k = i + 1; k <= this->invaders.size(); ++k)
                {
                    // Check value of k against size because we want the bottom row to shoot
                    // but short-circuit saves us from going out of bounds.
                    if (k != this->invaders.size() && !this->invaders[k][j]->isDead())
                    {
                        shoot = false;
                        break; // Don't need to keep checking.
                    }
                }

                if (shoot)
                {
                    sf::Vector2f invader_pos = invader->getSprite().getPosition();
                    this->shootLaser(invader_pos.x, invader_pos.y);
                }
            }
        }
    }
}

void InvaderFormation::moveLasers()
{
    this->handleCollisions();
    for(auto& laser : this->lasers)
        laser->move();
}

void InvaderFormation::removeHitLasers()
{
    for (unsigned i = 0; i < this->lasers.size(); ++i)
    {
        InvaderLaser *laser = lasers[i];
        if (laser->isHit())
            this->lasers.erase(lasers.begin() + i);
    }
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
            for (auto& invader_row : this->invaders)
            {
                for (auto& invader : invader_row)
                {
                    invader->move();
                    if (invader->checkHitEdge(Globals::SCREEN_WIDTH))
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

    for (auto& invader_row : this->invaders)
    {
        for (auto& invader : invader_row)
        {
            invader->dropDown(this->SHIELD_LINE);
            invader->reverseDir();
        }
    }

    // Also increase the rate that Invaders fire
    this->increaseFire(250);
}

void InvaderFormation::checkHit(PlayerLaser &laser, unsigned &game_score)
{
    for (auto& invader_row : this->invaders)
    {
        for (auto& invader : invader_row)
        {
            if (!invader->isDead() && invader->getSprite().getGlobalBounds().intersects(laser.getShape().getGlobalBounds()))
            {
                invader->die();

                // Increases the main game score, originally defined in main()
                game_score += invader->getScoreValue();

                // Formation speeds up for every 2 Invaders killed.
                ++this->num_killed;
                if (!(this->num_killed % 2) && this->move_tick_max > 1)
                {
                    --this->move_tick_max;
                    if (this->move_tick >= this->move_tick_max)
                        this->move_tick = this->move_tick_max - 1; // This is to keep the formation moving
                }

                // Also increase fire rate.
                this->increaseFire(10);

                this->death_snd.play();
                laser.stop();

                return; // Only 1 Invader can be hit at a time, so this saves time.
            }
        }

    }
}



void InvaderFormation::updateLasers()
{
    this->removeHitLasers();
    this->handleCollisions();
    this->moveLasers();
    this->shootLasers();
}

void InvaderFormation::drawLasers()
{
    for(auto& laser : this->lasers)
        //this->window.draw(laser->getSprite());
        laser->draw(this->window);
}

InvaderFormation::InvaderFormation(sf::RenderWindow &window, Textures &textures, Earth &earth, SoundFx &step1, SoundFx &step2, SoundFx &step3, SoundFx &step4, SoundFx &death_snd): window(window), earth(earth), move_tick(0), move_tick_max(MOVE_TICK_MAX_START), move_tick_change(MOVE_TICK_CHANGE_START), step_on(1), num_killed(0), has_hit_edge(false), shot_chance(SHOT_CHANCE_START), step1(step1), step2(step2), step3(step3), step4(step4), death_snd(death_snd)
{
    // Vector for each row in the formation
    InvaderRow small_invaders;
    InvaderRow medium_invaders1;
    InvaderRow medium_invaders2;
    InvaderRow large_invaders1;
    InvaderRow large_invaders2;

    for (unsigned i = 1; i <= this->ROWS; ++i)
    {
        small_invaders.push_back(new Invader(textures, Invader::SMALL));
        medium_invaders1.push_back(new Invader(textures, Invader::MEDIUM));
        medium_invaders2.push_back(new Invader(textures, Invader::MEDIUM));
        large_invaders1.push_back(new Invader(textures, Invader::LARGE));
        large_invaders2.push_back(new Invader(textures, Invader::LARGE));
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
    for (auto& invader_row : this->invaders)
    {
        for (auto& invader : invader_row)
            delete invader;

        invader_row.clear();
    }
    this->invaders.clear();

    // Destroy lasers
    for (auto &laser : this->lasers)
        delete laser;
    this->lasers.clear();
}

void InvaderFormation::update(PlayerLaser &laser, unsigned &game_score)
{
    this->move();
    this->checkHit(laser, game_score);
    this->updateLasers();
}

void InvaderFormation::draw()
{
    for (auto& invader_row : this->invaders)
    {
        for (auto& invader : invader_row)
        {
            if (!invader->isDead() || (invader->isDead() && invader->isExploding()))
                this->window.draw(invader->getSprite());
        }
    }
}

void InvaderFormation::setShieldLine(const unsigned shield_line)
{
    this->SHIELD_LINE = shield_line;
}
