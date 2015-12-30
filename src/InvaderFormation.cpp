#include "../inc/globals.hpp"
#include "../inc/misc.hpp"
#include "../inc/InvaderFormation.hpp"
#include "../inc/CoreCannon.hpp"

void InvaderFormation::reset(unsigned wave_on)
{
    this->move_tick = 0;
    this->move_tick_max = MOVE_TICK_MAX_START;
    this->move_tick_change = MOVE_TICK_CHANGE_START;
    this->step_on = 1;
    this->num_killed = 0;
    this->has_hit_edge = false;
    this->shot_chance = this->SHOT_CHANCE_START;

    this->removeLasers();

    for (unsigned i = 0; i < this->invaders.size(); ++i)
    {
        for (unsigned j = 0; j < this->invaders[i].size(); ++j)
            this->invaders[i][j]->reset(this->STARTX + (j * this->XGAP), (this->STARTY + (wave_on * Invader::getHeight())) + (i * this->YGAP));
    }
}

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

void InvaderFormation::shootLaser(unsigned x, unsigned y, const bool will_hurt, Invader &owner)
{
    // Normal lasers have a slightly greater chance of being created.
    unsigned dice_roll = Misc::random(1, 10);
    if (dice_roll <= 6)
        this->lasers.push_back(new NormalInvaderLaser(x, y, this->SHIELD_LINE, will_hurt, owner));
    else
        this->lasers.push_back(new PoweredInvaderLaser(x, y, this->SHIELD_LINE, will_hurt, owner));
}

void InvaderFormation::handleCollisions(Explosions &explosions, PlayerLaser &player_laser)
{
    for (unsigned i = 0; i < this->lasers.size(); ++i)
    {
        InvaderLaser *laser = this->lasers[i];

        // Check collision with earth
        if (laser->checkCollide(earth.getSprite().getGlobalBounds()))
        {
            earth.destroy(laser->getX());
            laser->setHit();
            explosions.newExplosion(sf::Color::Green, laser->getX(), laser->getY());
        }

        // Check collision with player laser
        if (laser->checkCollide(player_laser.getShape().getGlobalBounds()))
        {
            // Player laser always gets destroyed.
            explosions.newExplosion(sf::Color::White, laser->getX(), laser->getY());
            player_laser.stop();

            // Normal lasers have a 1 in 3 chance of being destroyed if hit by player laser.
            if (laser->getType() == InvaderLaser::LaserType::NORMAL && (Misc::random(1, 3) == 2))
                laser->setHit();
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

            // Only shoot if Invader is alive and hits the jackpot, and has less than 3 lasers on screen already.
            if (!invader->isDead() && invader->getLasersOnScreen() < 3 && this->toShootOrNah())
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
                    // If the Invader is right above the player, it's laser won't hurt.
                    this->shootLaser(invader_pos.x, invader_pos.y, invader->getSprite().getPosition().y < (this->INVADE_LINE - 40), *invader);
                }
            }
        }
    }
}

void InvaderFormation::moveLasers(Explosions &explosions, PlayerLaser &player_laser)
{
    this->handleCollisions(explosions, player_laser);
    for(auto& laser : this->lasers)
        laser->move();
}

void InvaderFormation::removeHitLasers()
{
    for (unsigned i = 0; i < this->lasers.size(); ++i)
    {
        InvaderLaser *laser = lasers[i];
        if (laser->isHit())
        {
            delete laser;
            this->lasers.erase(lasers.begin() + i);
        }
    }
}

bool InvaderFormation::move(CoreCannon &cannon, PlayerLaser &player_laser, UFO &ufo, LivesDisplay &lives_disp, Explosions &explosions)
{
    // The last Invader moves faster to the left than the right.
    if (this->getNumKilled() == (this->getTotal() - 1))
    {
        if (this->invaders[0][0]->getMoveDir() == 1)
            this->move_tick_max = 2;
        else
            this->move_tick_max = 1;
    }

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
                    // If Invader has made it far enough down, game over.
                    if (invader->getSprite().getPosition().y >= this->INVADE_LINE)
                    {
                        cannon.die(*this, player_laser, ufo, explosions);
                        lives_disp.setLives(0);
                    }

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
    // Don't let Invaders get too fast.
    if (this->move_tick_max > 2)
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
    this->increaseFire(10);
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

                ++this->num_killed;

                // If last Invader, move fast as possible.
                if (this->getNumKilled() == (this->getTotal() - 1))
                {
                    this->move_tick = 0;
                    this->move_tick_max = 1;
                }

                // Formation speeds up for every 6 Invaders killed.
                else if (!(this->num_killed % 6) && this->move_tick_max > 1)
                {
                    this->move_tick_max -= 5;
                    
                    // This is to keep the formation moving
                    if (this->move_tick >= this->move_tick_max)
                        this->move_tick = this->move_tick_max - 1; 

                    // Don't let Invaders move too fast...
                    if (this->move_tick_max < 2)
                        this->move_tick_max = 2;
                }

                // Also increase fire rate.
                this->increaseFire(17);

                this->death_snd.play();
                laser.stop();

                return; // Only 1 Invader can be hit at a time, so this saves time.
            }
        }

    }
}

void InvaderFormation::updateLasers(Explosions &explosions, PlayerLaser &player_laser)
{
    this->removeHitLasers();
    this->handleCollisions(explosions, player_laser);
    this->moveLasers(explosions, player_laser);
    this->shootLasers();
}

void InvaderFormation::removeLasers()
{
    // Destroy lasers
    for (auto& laser : this->lasers)
        delete laser;
    this->lasers.clear();
}

void InvaderFormation::drawLasers()
{
    for(auto& laser : this->lasers)
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

    this->reset(); 
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

    this->removeLasers();
}

void InvaderFormation::update(PlayerLaser &laser, CoreCannon &cannon, PlayerLaser &player_laser, UFO &ufo, LivesDisplay &lives_disp, Explosions &explosions, unsigned &game_score)
{
    this->move(cannon, player_laser, ufo, lives_disp, explosions);
    this->checkHit(laser, game_score);
    this->updateLasers(explosions, player_laser);
}

void InvaderFormation::draw(int amount)
{
    // Draw rows from the bottom up
    // The decrement is in the body of the loop because it needs to happen before the first iteration.
    // My previous setup "worked" but resulted in undefined behavior.
    // And apparently reverse iterators are slower to dereference so I didn't use them here.
    for (auto iter = this->invaders.end(); iter != this->invaders.begin(); /* intentionally empty */)
    {
        --iter; // end() can't be dereferenced, so immediately decrement the iterator.

        for (auto& invader : *iter)
        {
            if (!invader->isDead() || (invader->isDead() && invader->isExploding()))
            {
                this->window.draw(invader->getSprite());
                --amount;

                // The default for amount is -1, so if left at default,
                // this will never get ran, which means all Invaders will be drawn.
                if (amount == 0)
                    return;
            }
        }
    }
}

void InvaderFormation::setShieldLine(const unsigned shield_line)
{
    this->SHIELD_LINE = shield_line;
}
