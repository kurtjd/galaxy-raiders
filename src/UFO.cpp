#include <sstream>
#include "../inc/UFO.hpp"
#include "../inc/globals.hpp"
#include "../inc/misc.hpp"
#include "../inc/game.hpp"

bool UFO::toAppearOrNah()
{
    return Misc::random(1, this->APPEAR_CHANCE) == 1;
}

void UFO::appear()
{
    this->death_tick = this->DEATH_TICK_MAX;
    this->score_tick = this->SCORE_TICK_MAX;
    this->exploding = false;
    this->show_score = false;
    this->on_screen = true;

    // Have to redo this every time because when killed, its texture changes.
    this->sprite.setTexture(this->ufo_txtr, true);
    this->sprite.setPosition(0 + 10, this->Y);

    // The image is a little big so shrink it.
    this->sprite.setScale(this->SCALE, this->SCALE);
    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().width / 2);

    this->move_sound.play(true);
}

void UFO::move()
{
    this->sprite.move(this->SPEED, 0);

    if (this->sprite.getPosition().x > Globals::SCREEN_WIDTH)
    {
        this->on_screen = false;
        this->sprite.setPosition(999, 999);
        this->move_sound.stop();
    }
}

void UFO::handleHit(PlayerLaser &laser, unsigned &game_score)
{
    if (laser.isShooting() && this->sprite.getGlobalBounds().intersects(laser.getShape().getGlobalBounds()))
    {
        // Pick a random score to add to main score.
        unsigned score = this->SCORES[Misc::random(0, this->SCORES.size() - 1)];
        game_score += score;

        std::ostringstream score_txt;
        score_txt << score;
        this->tmp_score_txt = score_txt.str();

        this->exploding = true;

        this->sprite.setTexture(this->explode_txtr, true);
        this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().width / 2);
        this->sprite.setColor(sf::Color::Red); // The original exploding texture is white.
        this->sprite.setScale(1, 1);

        laser.stop();

        this->move_sound.stop();
        this->killed_sound.play();
    }
}

void UFO::incDeathTick()
{
    --this->death_tick;
    if (this->death_tick <= 0)
    {
        this->exploding = false;
        this->show_score = true;
    }
}

void UFO::incScoreTick()
{
    --this->score_tick;
    if (this->score_tick <= 0)
    {
        this->on_screen = false;
        this->sprite.setPosition(999, 999);
    }
}

UFO::UFO(Textures &textures, SoundFx &ufo_move_snd, SoundFx &ufo_killed_snd): SCORES({50, 100, 150}), ufo_txtr(textures.UFO), explode_txtr(textures.INVADER_DEATH), on_screen(false), exploding(false), show_score(false), death_tick(DEATH_TICK_MAX), score_tick(SCORE_TICK_MAX), move_sound(ufo_move_snd), killed_sound(ufo_killed_snd)
{
}

void UFO::update(PlayerLaser &laser, unsigned &game_score)
{
    // If not on screen, roll to see if it will appear.
    if (!this->on_screen && this->toAppearOrNah())
        this->appear();
    else if (this->on_screen)
    {
        // If the UFO hasn't been shot, it moves across the screen.
        if (!this->exploding && !this->show_score)
        {
            this->move();
            this->handleHit(laser, game_score);
        }
        // Counter to display explosion
        else if (this->exploding)
            this->incDeathTick();            
        // Counter to display score value
        else if (this->show_score)
            this->incScoreTick();            
    }
}

void UFO::draw(sf::RenderWindow &window)
{
    if (this->on_screen)
    {
        // Either draw the sprite or the score value depending on the state the UFO is in.
        if (!this->show_score)
            window.draw(this->sprite);
        else
            Game::draw_text(window, tmp_score_txt, this->sprite.getPosition().x - 5, this->Y - 15, sf::Color::Red);
    }
}
