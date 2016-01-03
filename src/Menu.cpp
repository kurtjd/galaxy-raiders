#include <sstream>
#include "Menu.hpp"
#include "game.hpp"

Menu::Menu(Textures &textures, ScoreDisplay &score_disp): score_disp(score_disp), str_char_on(0), line_on(1), sprite_drawn(false), display_scores(false)
{
    this->ufo.setTexture(textures.UFO_MENU);
    this->small_invader.setTexture(textures.SMALL_INV_2);
    this->medium_invader.setTexture(textures.MEDIUM_INV_1);
    this->large_invader.setTexture(textures.LARGE_INV_1);

    // The large Invader is green on the menu screen.
    this->large_invader.setColor(sf::Color::Green);

    // UFO texture is a little big
    this->ufo.setScale(0.6, 0.6);

    this->ufo.setPosition((Globals::SCREEN_WIDTH / 2) - 145, 381);
    this->small_invader.setPosition((Globals::SCREEN_WIDTH / 2) - 137, 420);
    this->medium_invader.setPosition((Globals::SCREEN_WIDTH / 2) - 142, 465);
    this->large_invader.setPosition((Globals::SCREEN_WIDTH / 2) - 142, 510);
}

void Menu::reset()
{
    this->line_on = 1;
    this->str_char_on = 0;
    this->sprite_drawn = false;
    this->display_scores = false;
}

void Menu::drawLine(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, const unsigned wait, const unsigned line_num, sf::Sprite *sprite, sf::Color color, unsigned size)
{
    // If the menu isn't at the text's line yet, don't draw anything.
    if (line_num > this->line_on)
        return;

    // If the menu has passed the text's line, just draw the line all at once.
    else if (line_num < this->line_on)
    {
        if (sprite != nullptr)
            window.draw(*sprite);

        Game::draw_text(window, msg, x, y, color, size);
        return;
    }

    if (sprite != nullptr && this->display_scores)
    {
        window.draw(*sprite);
        if (!this->sprite_drawn)
        {
            sf::sleep(sf::milliseconds(wait));
            this->sprite_drawn = true;
        }
    }

    // If the menu is on the text's line, draw it letter by letter.
    std::ostringstream ss;
    for (unsigned i = 0; i <= this->str_char_on; ++i)
        ss << msg[i];

    if (this->str_char_on < msg.length())
        ++this->str_char_on;
    else
    { ++this->line_on;
        this->str_char_on = 0;
        this->sprite_drawn = false;
    }

    Game::draw_text(window, ss.str(), x, y, color, size);
    sf::sleep(sf::milliseconds(wait));
}

void Menu::draw(sf::RenderWindow &window)
{
    // Display credits...
    Game::draw_text(window, "P R O G R A M M E D    B Y    K U R T", 10, Globals::SCREEN_HEIGHT - 20, sf::Color::White, 12);

    // Score display and credit line will always show the same
    this->score_disp.draw(window);
    Game::draw_text(window, "C R E D I T    0 0", 550, 687); 
    
    this->drawLine(window, "P L A Y", (Globals::SCREEN_WIDTH / 2) - 35, 180, this->PAUSE, 1);
    this->drawLine(window, "S P A C E         I N V A D E R S", (Globals::SCREEN_WIDTH / 2) - 150, 240, this->PAUSE, 2);

    // This line of the menu is always drawn at once.
    if (this->line_on >= 3)
    {
        Game::draw_text(window, "* S C O R E    A D V A N C E    T A B L E *", (Globals::SCREEN_WIDTH / 2) - 225, 340);

        if (this->line_on == 3)
            ++this->line_on;
        
        // Prevents the next line from being drawn too soon.
        else if (this->line_on == 4 && this->str_char_on == 1)
        {
            sf::sleep(sf::milliseconds(500));
            this->display_scores = true;
        }
    }

    // These include a sprite's address because they draw a sprite in their line
    this->drawLine(window, " = ?    M Y S T E R Y", (Globals::SCREEN_WIDTH / 2) - 95, 380, this->PAUSE, 4, &this->ufo);
    this->drawLine(window, " = 3 0    P O I N T S", (Globals::SCREEN_WIDTH / 2) - 95, 425, this->PAUSE, 5, &this->small_invader);
    this->drawLine(window, " = 2 0    P O I N T S", (Globals::SCREEN_WIDTH / 2) - 95, 470, this->PAUSE, 6, &this->medium_invader);
    this->drawLine(window, " =  1 0    P O I N T S", (Globals::SCREEN_WIDTH / 2) - 95, 515, this->PAUSE, 7, &this->large_invader, sf::Color::Green, 24);

    Game::draw_text(window, "P R E S S                        T O    P L A Y", (Globals::SCREEN_WIDTH / 2) - 200, 600);
    Game::draw_text(window, "E N T E R", (Globals::SCREEN_WIDTH / 2) - 70, 600, sf::Color::Green);
}
