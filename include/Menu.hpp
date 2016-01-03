#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include "Textures.hpp"
#include "ScoreDisplay.hpp"

class Menu
{
private:
    static constexpr unsigned PAUSE = 10;

    // The only sprites on the menu screen. Everything else is text.
    sf::Sprite ufo;
    sf::Sprite small_invader;
    sf::Sprite medium_invader;
    sf::Sprite large_invader;

    ScoreDisplay &score_disp;

    // Used by drawLine to track which character it is currently on.
    unsigned str_char_on;

    unsigned line_on;

    bool sprite_drawn;
    bool display_scores;

public:
    Menu(Textures &textures, ScoreDisplay &score_disp);

    void reset();

    // Draws a string with a specified pause between each letter.
    // Pointer used for sprite instead of reference because sprite can be null
    void drawLine(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, const unsigned wait, const unsigned line_num, sf::Sprite *sprite = nullptr, sf::Color color = sf::Color::White, unsigned size = 24);

    void draw(sf::RenderWindow &window);

};

#endif
