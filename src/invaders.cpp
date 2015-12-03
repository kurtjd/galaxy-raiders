#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "PlayerShip.hpp"
#include "Shield.hpp"

/* Display Constants */
const std::string SCREEN_TITLE = "Space Invaders!";
const unsigned SCREEN_WIDTH = 700;
const unsigned SCREEN_HEIGHT = 700;
const unsigned FRAME_RATE = 30;
const sf::Color BG_COLOR = sf::Color::Black;

sf::Image load_sprites(std::string img)
{
    sf::Image spritesheet;
    spritesheet.loadFromFile(img);
    return spritesheet;
}

//Creates shields across the screen
void init_shields(sf::Image &spritesheet, std::vector<Shield*> &shields)
{
    // Create shields on the heap so they don't go out of scope.
    // This loop creates 4 shields across the screen.
    for (unsigned i = 45; i < SCREEN_WIDTH; i += 175)
        shields.push_back(new Shield(spritesheet, i));
}

//Remove shields from memory
void del_shields(std::vector<Shield*> &shields)
{
    for (unsigned i = 0; i < shields.size(); ++i)
        delete shields[i];

    shields.clear();
}

// Draws the shields to the screen
void draw_shields(sf::RenderWindow &window, std::vector<Shield*> &shields)
{
    for (unsigned i = 0; i < shields.size(); ++i)
        window.draw(shields[i]->getSprite());
}

int main()
{
    // Create and render game window.
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
    window.setFramerateLimit(FRAME_RATE);

    // Load spritesheet
    sf::Image spritesheet = load_sprites("../sprites/invader_sprites.png");

    // Create screenline
    sf::RectangleShape screenline(sf::Vector2f(SCREEN_WIDTH, 2));
    screenline.setPosition(0, 650);
    screenline.setFillColor(sf::Color::Green);

    // Create shields vector
    std::vector<Shield*> shields;
    
    // Initialize shields
    init_shields(spritesheet, shields);

    // Create player ship
    PlayerShip playership = PlayerShip(spritesheet, 250);


    // Begin game loop
    while (window.isOpen())
    {
        // Check for input
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                del_shields(shields);
                window.close();
                break;

            default:
                break;
            }
        }

        // Display window
        window.clear(BG_COLOR);
        window.draw(playership.getAliveSprite());
        draw_shields(window, shields);
        window.draw(screenline);
        window.display();
    }
}
