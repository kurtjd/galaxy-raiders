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
    // Creates an Image object to be used as a texture for sprites.
    sf::Image load_sprites(const std::string img);

    // Handles any events that pop up (mainly window close)
    void handle_events(sf::Window &window);

    // Handles real-time keyboard input
    void real_time_key(CoreCannon &cannon, PlayerLaser &player_laser);

    // Update all game objects
    void update_objects(CoreCannon &cannon, PlayerLaser &player_laser, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields);

    // A wrapper for drawing player laser to check if it is shooting
    void draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser);

    // Draws text in space invaders font to the screen at given position
    void draw_text(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y);

    // Draw all objects
    void draw_objects(sf::RenderWindow &window, ScoreDisplay &score_disp, LivesDisplay &lives_disp, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields, CoreCannon &cannon, PlayerLaser &playerlaser, Earth &earth);

    // Calculates the current FPS and updates the window title with it.
    void updateFPS(sf::Window &window, const sf::Clock &fps_clock, float &fps_timer);

};

#endif
