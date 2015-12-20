#include "../inc/globals.hpp"

// Game state is useful to all objects so make it global.
// Globals are evil my ass...
Globals::States Globals::GAME_STATE = Globals::States::WAVE_SETUP;
