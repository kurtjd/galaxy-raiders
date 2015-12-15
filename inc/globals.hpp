#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <SFML/Graphics.hpp>

/* Global constants that are useful for all classes. */

namespace Globals
{
    const std::string SCREEN_TITLE = "Space Invaders!";
    constexpr unsigned SCREEN_WIDTH = 800;
    constexpr unsigned SCREEN_HEIGHT = 730;
    constexpr unsigned FRAME_RATE = 60;
    const sf::Color BG_COLOR = sf::Color::Black;

    const std::string SOUNDS_PATH = "sounds/";
    const std::string SPRITES_PATH = "sprites/";
    const std::string FONTS_PATH = "fonts/";
};

#endif
