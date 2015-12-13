#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../inc/PlayerLaser.hpp"
#include "../inc/InvaderFormation.hpp"
#include "../inc/ShieldWall.hpp"
#include "../inc/CoreCannon.hpp"
#include "../inc/Earth.hpp"

/* Functions that deal with the game but don't belong in a class. */

namespace Game
{
    // Creates an Image object to be used as a texture for sprites.
    sf::Image load_sprites(std::string img);

    // A wrapper for drawing player laser to check if it is shooting
    void draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser);

    // Draw all objects
    void draw_objects(sf::RenderWindow &window, InvaderFormation &invaders, ShieldWall &shields, CoreCannon &cannon, PlayerLaser &playerlaser, Earth &earth);

    // Calculates the current FPS and updates the window title with it.
    void updateFPS(sf::Window &window, sf::Clock &fps_clock, float &fps_timer);

};

#endif
