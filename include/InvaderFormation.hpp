#ifndef INVADERFORMATION_H
#define INVADERFORMATION_H

#include <SFML/Graphics.hpp>
#include "SoundFx.hpp"
#include "Invader.hpp"
#include "NormalInvaderLaser.hpp"
#include "PoweredInvaderLaser.hpp"
#include "PlayerLaser.hpp"
#include "Earth.hpp"
#include "LivesDisplay.hpp"
#include "Explosions.hpp"
#include "PlayerLaser.hpp"

class CoreCannon;

/* Represents the entire Space Invader formation.
 * Coordinates movement and firing of all Space Invaders. */

typedef std::vector<Invader*> InvaderRow;
typedef std::vector<InvaderRow> InvaderVector2D;
typedef std::vector<InvaderLaser*> Lasers;

class InvaderFormation
{
private:
    // Size of formation
    static constexpr unsigned COLUMNS = 5;
    static constexpr unsigned ROWS = 11;

    // Where the formation starts on screen
    static constexpr unsigned STARTX = 120;
    const unsigned STARTY = 150;

    // The space between each invader in the formation
    static constexpr unsigned XGAP = 55;
    static constexpr unsigned YGAP = 50;

    static constexpr unsigned WAVE_SHIFT_Y = 50;

    static constexpr unsigned INVADE_LINE = Globals::SCREEN_HEIGHT - 110;

    // Gameplay
    static constexpr int MOVE_TICK_MAX_START = 45;
    static constexpr int MOVE_TICK_CHANGE_START = 1;//5;

    // Chance of each Invader shooting: 1/SHOT_CHANCE
    static constexpr int SHOT_CHANCE_START = 1000;

    unsigned SHIELD_LINE;

    sf::RenderWindow &window;
    InvaderVector2D invaders;

    // Earth, the line at the bottom of the screen.
    Earth &earth;

    // When move_tick hits move_tick_max, the formation moves
    // move_tick_max is lowered every time formation hits edge of screen
    int move_tick;
    int move_tick_max;
    int move_tick_change;

    unsigned step_on;
    unsigned num_killed; // Number of Invaders killed.

    bool has_hit_edge;

    int shot_chance;

    // Sounds for stepping
    SoundFx &step1;
    SoundFx &step2;
    SoundFx &step3;
    SoundFx &step4;
    SoundFx &death_snd;


    // Check if invaders are exploding and increment tick
    void incDeathTick();

    // Cycles though 4 different sounds every step.
    void playStepSound();

    // Increases rate of fire by lowering shot chance
    void increaseFire(const int amount);

    // Private methods dealing with lasers
    bool toShootOrNah() const;
    void shootLaser(const unsigned x, const unsigned y, const bool will_hurt, Invader &owner);
    void handleCollisions(Explosions &explosions, PlayerLaser &player_laser);
    void shootLasers();
    void moveLasers(Explosions &explosions, PlayerLaser &player_laser);
    void removeHitLasers();
    void updateLasers(Explosions &explosions, PlayerLaser &player_laser);

    // Contains all lasers currently being fired by Invaders
    Lasers lasers;

    // This is bool so main game can keep track when Invader actually moved
    bool move(CoreCannon &cannon, PlayerLaser &player_laser, UFO &ufo, LivesDisplay &lives_disp, Explosions &explosions);

    // Increase speed, drop down, and reverse direction!
    void shift();

    void checkHit(PlayerLaser &laser, unsigned &game_score);

public:
    InvaderFormation(sf::RenderWindow &window, Textures &textures, Earth &earth, SoundFx &step1, SoundFx &step2, SoundFx &step3, SoundFx &step4, SoundFx &death_snd);
    ~InvaderFormation();
    Lasers& getLasers(){ return this->lasers; }
    InvaderVector2D& getInvaders(){ return this->invaders; }
    unsigned getTotal() const { return this->COLUMNS * this->ROWS; }
    unsigned getNumKilled() const { return this->num_killed; }

    void reset(unsigned wave_on = 0);

    void update(PlayerLaser &laser, CoreCannon &cannon, PlayerLaser &player_laser, UFO &ufo, LivesDisplay &lives_disp, Explosions &explosions, unsigned &game_score);

    void draw(int amount = -1);
    void drawLasers();

    void setShieldLine(const unsigned shield_line);

    void removeLasers();

};

#endif
