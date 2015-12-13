#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <SFML/Graphics.hpp>

/* Global constants that are useful for all classes. */

namespace Globals
{
    const std::string SCREEN_TITLE = "Space Invaders!";
    const unsigned SCREEN_WIDTH = 800;
    const unsigned SCREEN_HEIGHT = 730;
    const unsigned FRAME_RATE = 60;
    const sf::Color BG_COLOR = sf::Color::Black;

    const std::string SOUNDS_PATH = "sounds/";
    const std::string SPRITES_PATH = "sprites/";
};

#endif
