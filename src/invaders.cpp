#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SoundFx.hpp"
#include "InvaderFormation.hpp"
#include "ShieldWall.hpp"
#include "CoreCannon.hpp"
#include "PlayerLaser.hpp"
#include "Earth.hpp"

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

// A wrapper for drawing player laser to check if it is shooting
void draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser)
{
    if (laser.isShooting())
        window.draw(laser.getShape());
}

// Draw all objects
void draw_objects(sf::RenderWindow &window, InvaderFormation &invaders, ShieldWall &shields, CoreCannon &cannon, PlayerLaser &playerlaser, Earth &earth)
{
    window.clear(BG_COLOR);
    invaders.draw();
    shields.draw();
    window.draw(cannon.getSprite());
    draw_player_laser(window, playerlaser);
    window.draw(earth.getShape());
    window.display();
}


int main()
{
    /*// Setup FPS timer
    sf::Clock fps_clock;
    float fps_timer = fps_clock.getElapsedTime().asSeconds();*/

    // Create and render game window.
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), SCREEN_TITLE);
    window.setFramerateLimit(FRAME_RATE);

    // Load sounds
    SoundFx shoot_snd("../sounds/shoot_laser.wav");
    SoundFx invader_death_snd("../sounds/invader_death.wav");
    SoundFx invader_step1_snd("../sounds/invader_step1.wav");
    SoundFx invader_step2_snd("../sounds/invader_step2.wav");
    SoundFx invader_step3_snd("../sounds/invader_step3.wav");
    SoundFx invader_step4_snd("../sounds/invader_step4.wav");

    // Load spritesheet
    sf::Image spritesheet = load_sprites("../sprites/invader_sprites.png");

    // Create Invaders!
    InvaderFormation invaders(window, spritesheet, invader_death_snd, SCREEN_WIDTH);

    // Create shields
    ShieldWall shields(window, spritesheet, SCREEN_WIDTH);

    // Create Core Cannon (player)
    CoreCannon cannon = CoreCannon(spritesheet, SCREEN_WIDTH / 2);
    
    // Create player laser
    PlayerLaser player_laser;
    
    // Create "Earth" (best name I could come up with
    // for the line at bottom of the screen)
    Earth earth(SCREEN_WIDTH);
    
    // Used to play invader move sounds
    unsigned step_on = 1;


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

        // Shoot laser
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player_laser.isShooting())
        {
            sf::Vector2f cannonpos = cannon.getSprite().getPosition();
            player_laser.shoot(cannonpos.x, cannonpos.y);

            shoot_snd.play();
        }

        /* Update objects */
        if (invaders.move())
        {
            // Invaders make 4 sounds in a loop on each step
            switch (step_on)
            {
            case 1:
                invader_step1_snd.play();
                break;

            case 2:
                invader_step2_snd.play();
                break;

            case 3:
                invader_step3_snd.play();
                break;

            case 4:
                invader_step4_snd.play();
                break;

            default:
                break;
            }


            ++step_on;
            if (step_on > 4)
                step_on = 1;
        }

        invaders.checkHit(player_laser);
        player_laser.move();

        /* Display window and draw objects */
        draw_objects(window, invaders, shields, cannon, player_laser, earth);

        //updateFPS(window, fps_clock, fps_timer);
    }
}
