#ifndef UFO_H
#define UFO_H

#include <string>
#include <array>
#include <SFML/Graphics.hpp>
#include "SoundFx.hpp"
#include "Textures.hpp"
#include "PlayerLaser.hpp"

class UFO
{
private:
    static constexpr double SCALE = 0.6;
    static constexpr unsigned Y = 120;
    static constexpr unsigned SPEED = 3;

    static constexpr unsigned DEATH_TICK_MAX = 55;
    static constexpr unsigned SCORE_TICK_MAX = 85;

    // The UFO appears at a 1/APPEAR_CHANCE rate.
    static constexpr unsigned APPEAR_CHANCE = 500;

    // UFO has 3 possible score values (defined in constructor initializer)
    const std::array<unsigned, 3> SCORES;

    sf::Texture &ufo_txtr;
    sf::Texture &explode_txtr;
    sf::Sprite sprite;

    bool on_screen;

    std::string tmp_score_txt;
    bool exploding;
    bool show_score;
    unsigned death_tick;
    unsigned score_tick;
    unsigned shots_fired;

    SoundFx &move_sound;
    SoundFx &killed_sound;

    bool toAppearOrNah();
    void appear();
    void move();
    void handleHit(PlayerLaser &laser, unsigned &game_score);
    void incDeathTick();
    void incScoreTick();

public:
    UFO(Textures &textures, SoundFx &ufo_move_snd, SoundFx &ufo_killed_snd);

    void reposition();
    void reset();

    void update(PlayerLaser &laser, unsigned &game_score);
    void draw(sf::RenderWindow &window);

    void pause();

    void incShotsFired();

};

#endif
