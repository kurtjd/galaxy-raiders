#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <SFML/Graphics.hpp>

class ScoreDisplay
{
private:
    static constexpr unsigned X = 0;
    static constexpr unsigned Y = 0;

    // Reference to the game score, which is a variable declared in main().
    const unsigned &game_score;

public:
    ScoreDisplay(const unsigned &score);

    void draw(sf::RenderWindow &window);

};

#endif
