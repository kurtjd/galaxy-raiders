#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../inc/SoundFx.hpp"
#include "../inc/ScoreDisplay.hpp"
#include "../inc/LivesDisplay.hpp"
#include "../inc/PlayerLaser.hpp"
#include "../inc/UFO.hpp"
#include "../inc/InvaderFormation.hpp"
#include "../inc/ShieldWall.hpp"
#include "../inc/CoreCannon.hpp"
#include "../inc/Earth.hpp"

/* Functions that deal with the game but don't belong in a class. */

namespace Game
{
    // Handles any events that pop up (mainly window close)
    void handle_events(sf::Window &window, UFO &ufo);

    // Handles real-time keyboard input
    void real_time_key(InvaderFormation &invaders, PlayerLaser &player_laser, CoreCannon &cannon, ShieldWall &shields, Earth &earth, UFO &ufo, unsigned &wave_on);

    // Update all game objects
    void update_objects(CoreCannon &cannon, PlayerLaser &player_laser, Earth &earth, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields, LivesDisplay &lives_disp, unsigned &game_score, unsigned &wave_on);

    // A wrapper for drawing player laser to check if it is shooting
    void draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser);

    // Draws text in space invaders font to the screen at given position
    void draw_text(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, sf::Color color = sf::Color::White, unsigned size = 24);

    // Draw all objects
    void draw_objects(sf::RenderWindow &window, ScoreDisplay &score_disp, LivesDisplay &lives_disp, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields, CoreCannon &cannon, PlayerLaser &playerlaser, Earth &earth, unsigned &wave_on);

    // Calculates the current FPS and updates the window title with it.
    void updateFPS(sf::Window &window, const sf::Clock &fps_clock, float &fps_timer);

    void pause(UFO &ufo);

    void handle_player_kill(InvaderFormation &invaders, PlayerLaser &player_laser, UFO &ufo);

    void setup_wave(InvaderFormation &invaders, PlayerLaser &player_laser, CoreCannon &cannon, ShieldWall &shields, Earth &earth, UFO &ufo, unsigned &wave_on, bool start_game = false);

    void draw_wave(InvaderFormation &invaders);

    void handle_game_over(sf::RenderWindow &window, ScoreDisplay &score_disp, LivesDisplay &lives_disp, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields, CoreCannon &cannon, PlayerLaser &playerlaser, Earth &earth, unsigned &wave_on);

    void reset_game(ScoreDisplay &score_disp, LivesDisplay &lives_disp, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields, CoreCannon &cannon, PlayerLaser &playerlaser, Earth &earth, unsigned &wave_on);

    void goto_menu(ScoreDisplay &score_disp, LivesDisplay &lives_disp, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields, CoreCannon &cannon, PlayerLaser &playerlaser, Earth &earth, unsigned &wave_on);

    void draw_menu(sf::RenderWindow &window);

    void play_game(InvaderFormation &invaders, PlayerLaser &player_laser, CoreCannon &cannon, ShieldWall &shields, Earth &earth, UFO &ufo, unsigned &wave_on);

};

#endif
