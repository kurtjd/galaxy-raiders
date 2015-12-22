#include "../inc/globals.hpp"
#include "../inc/game.hpp"
#include "../inc/CoreCannon.hpp"

void CoreCannon::flipFrame()
{
    if (this->frame_on == 1)
    {
        this->frame_on = 2;
        this->sprite.setTexture(this->textures.CORECANNON_DEATH_2, true);
    }
    else
    {
        this->frame_on = 1;
        this->sprite.setTexture(this->textures.CORECANNON_DEATH_1, true);
    }
}

void CoreCannon::reset()
{
    this->death_tick = this->DEATH_TICK_MAX;
    this->frame_tick = this->FRAME_TICK_MAX;
    this->frame_on = 1;
    this->hit = false;

    this->sprite.setTexture(this->textures.CORECANNON, true);
    this->sprite.setPosition(this->START_X, this->Y);

    // Put the point of origin in center of cannon.
    this->sprite.setOrigin(this->sprite.getTexture()->getSize().x / 2, this->sprite.getTexture()->getSize().y / 2);

    if (Globals::GAME_STATE != Globals::States::WAVE_SETUP && Globals::GAME_STATE != Globals::States::GAME_OVER && Globals::GAME_STATE != Globals::States::MENU)
        Globals::GAME_STATE = Globals::States::PLAY;
}

CoreCannon::CoreCannon(Textures &textures, SoundFx &killed_sound, const int startx): killed_sound(killed_sound), START_X(startx), textures(textures), frame_on(1), hit(false), death_tick(DEATH_TICK_MAX), frame_tick(FRAME_TICK_MAX)
{
    this->reset(); 
}

void CoreCannon::move(const int dir)
{
    // +/- 10 because it stops the cannon from going slightly off screen
    if (!this->hit && ((dir == 1 && (this->getX() < (Globals::SCREEN_WIDTH - (this->getWidth() / 2) - 10)))
        || (dir == -1 && (this->getX() > (0 + (this->getWidth() / 2) + 10)))))
        this->sprite.move(this->SPEED * dir, 0);
}

void CoreCannon::handleHit(InvaderFormation &invaders, PlayerLaser &player_laser, UFO &ufo)
{
    for (auto& laser : invaders.getLasers())
    {
        if (!this->hit && (laser->checkCollide(this->sprite.getGlobalBounds())))
        {
            this->hit = true;
            this->sprite.setTexture(this->textures.CORECANNON_DEATH_1, true);
            this->killed_sound.play();

            Game::handle_player_kill(invaders, player_laser, ufo);
            return;
        }
    }
}

void CoreCannon::update(InvaderFormation &invaders, PlayerLaser &player_laser, UFO &ufo, LivesDisplay &lives_disp)
{
    this->handleHit(invaders, player_laser, ufo);
    if (this->hit)
    {
        --this->death_tick;
        if (this->death_tick <= 0)
        {
            lives_disp.removeLife();
            ufo.pause(); // Unpauses the UFO... (yeah I know)
            this->reset();
        }

        --this->frame_tick;
        if (this->frame_tick <= 0)
        {
            this->flipFrame();
            this->frame_tick = this->FRAME_TICK_MAX;
        }
    }
}
