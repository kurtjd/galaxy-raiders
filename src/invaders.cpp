#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "CoreCannon.hpp"
#include "Shield.hpp"
#include "PlayerBullet.hpp"
#include "Earth.hpp"
#include "Invader.hpp"

/* Display Constants */
const std::string SCREEN_TITLE = "Space Invaders!";
const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 730;
const unsigned FRAME_RATE = 60;
const sf::Color BG_COLOR = sf::Color::Black;

/*// Calculates the current FPS and updates the window title with it.
void updateFPS(sf::Window &window, sf::Clock &fps_clock, float &fps_timer)
{
    float fps = 1.0f / (fps_clock.getElapsedTime().asSeconds() - fps_timer);
    std::ostringstream title;
    title << "Space Invaders! - " << round(fps) << "fps";
    window.setTitle(title.str());
    fps_timer = fps_clock.getElapsedTime().asSeconds();
}*/

// Creates an Image object to be used as a texture for sprites.
sf::Image load_sprites(std::string img)
{
    sf::Image spritesheet;
    spritesheet.loadFromFile(img);
    return spritesheet;
}

// Create Invader formation
void init_invaders(sf::Image &spritesheet, std::vector<std::vector<Invader*> > &invaders)
{
    // Vector for each row in the formation
    std::vector<Invader*> small_invaders;
    std::vector<Invader*> medium_invaders1;
    std::vector<Invader*> medium_invaders2;
    std::vector<Invader*> large_invaders1;
    std::vector<Invader*> large_invaders2;

    // Create each row (each row has 11 invaders)
    for (unsigned i = 1; i <= 11; ++i)
    {
        small_invaders.push_back(new Invader(spritesheet, Invader::SMALL));
        medium_invaders1.push_back(new Invader(spritesheet, Invader::MEDIUM));
        medium_invaders2.push_back(new Invader(spritesheet, Invader::MEDIUM));
        large_invaders1.push_back(new Invader(spritesheet, Invader::LARGE));
        large_invaders2.push_back(new Invader(spritesheet, Invader::LARGE));
    }

    // Now add each row to the main vector
    invaders.push_back(small_invaders);
    invaders.push_back(medium_invaders1);
    invaders.push_back(medium_invaders2);
    invaders.push_back(large_invaders1);
    invaders.push_back(large_invaders2);

    // Setup starting positions
    unsigned startx = 120;
    unsigned starty = 100;

    for (unsigned i = 0; i < invaders.size(); ++i)
    {
        for (unsigned j = 0; j < invaders[i].size(); ++j)
            invaders[i][j]->getSprite().setPosition(startx + (j * 55), starty + (i * 50));
    }
}

// Remove Invaders from memory
void del_invaders(std::vector<std::vector<Invader*> > &invaders)
{
    for (unsigned i = 0; i < invaders.size(); ++i)
    {
        for (unsigned j = 0; j < invaders[i].size(); ++j)
            delete invaders[i][j];

        invaders[i].clear();
    }

    invaders.clear();
}

// Draws the invaders to the screen
void draw_invaders(sf::RenderWindow &window, std::vector<std::vector<Invader*> > &invaders)
{
    for (unsigned i = 0; i < invaders.size(); ++i)
    {
        for (unsigned j = 0; j < invaders[i].size(); ++j)
        {
            Invader *invader = invaders[i][j];
            if (!invader->isDead())
                window.draw(invader->getSprite());
        }
    }
}

// Creates shields across the screen
void init_shields(sf::Image &spritesheet, std::vector<Shield*> &shields)
{
    // Create shields on the heap so they don't go out of scope.
    // This loop creates 4 shields across the screen.
    // 97 is start point, -5 is to stop part of 5th shield from drawing at edge
    for (unsigned i = 97; i < SCREEN_WIDTH - 5; i += 175)
        shields.push_back(new Shield(spritesheet, i));
}

// Remove shields from memory
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

// A wrapper for drawing player bullet to check if it is shooting
void draw_player_bullet(sf::RenderWindow &window, PlayerBullet &bullet)
{
    if (bullet.isShooting())
        window.draw(bullet.getShape());
}

// Draw all objects
void draw_objects(sf::RenderWindow &window, std::vector<std::vector<Invader*> > &invaders, CoreCannon &cannon, PlayerBullet &playerbul, Earth &earth, std::vector<Shield*> &shields)
{
    window.clear(BG_COLOR);
    draw_invaders(window, invaders);
    draw_shields(window, shields);
    window.draw(cannon.getAliveSprite());
    draw_player_bullet(window, playerbul);
    window.draw(earth.getShape());
    window.display();
}

// Check collision between player bullet and Invaders
void check_invader_hit(std::vector<std::vector<Invader*> > &invaders, PlayerBullet &bullet)
{
    for (unsigned i = 0; i < invaders.size(); ++i)
    {
        for (unsigned j = 0; j < invaders[i].size(); ++j)
        {
            Invader *invader = invaders[i][j];
            if (!invader->isDead() && invader->getSprite().getGlobalBounds().intersects(bullet.getShape().getGlobalBounds()))
            {
                invader->die();
                bullet.stop();
            }
        }

    }
}


int main()
{
    /*// Setup FPS timer
    sf::Clock fps_clock;
    float fps_timer = fps_clock.getElapsedTime().asSeconds();*/

    // Create and render game window.
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
    window.setFramerateLimit(FRAME_RATE);

    // Load spritesheet
    sf::Image spritesheet = load_sprites("../sprites/invader_sprites.png");

    // Create Invaders!
    std::vector<std::vector<Invader*> > invaders;
    init_invaders(spritesheet, invaders);

    // Create shields
    std::vector<Shield*> shields;
    init_shields(spritesheet, shields);

    // Create Core Cannon (player)
    CoreCannon cannon = CoreCannon(spritesheet, SCREEN_WIDTH / 2);
    
    // Create player bullet
    PlayerBullet player_bul;
    
    // Create "Earth" (best name I could come up with
    // for the line at bottom of the screen)
    Earth earth(SCREEN_WIDTH);


    /* Begin game loop */
    while (window.isOpen())
    {
        // Check for events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                del_shields(shields);
                del_invaders(invaders);
                window.close();
                break;

            default:
                break;
            }
        }

        /* Handle keyboard input (this is realtime keyboard input, as opposed to 'event-based') */
        // Move Core Cannon
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && cannon.getX() < (SCREEN_WIDTH - (cannon.getWidth() / 2) - 10))
            cannon.move(1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && cannon.getX() > (0 + (cannon.getWidth() / 2) + 10))
            cannon.move(-1);

        // Shoot bullet
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player_bul.isShooting())
        {
            sf::Vector2f cannonpos = cannon.getAliveSprite().getPosition();
            player_bul.shoot(cannonpos.x, cannonpos.y);
        }

        /* Update objects */
        check_invader_hit(invaders, player_bul);

        if (player_bul.isShooting())
            player_bul.move();

        /* Display window and draw objects */
        draw_objects(window, invaders, cannon, player_bul, earth, shields);

        //updateFPS(window, fps_clock, fps_timer);
    }
}
