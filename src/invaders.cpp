#include <SFML/Graphics.hpp>
#include "../inc/globals.hpp"
#include "../inc/misc.hpp"
#include "../inc/game.hpp"
#include "../inc/SoundFx.hpp"

int main()
{
    // Setup FPS timer
    sf::Clock fps_clock;
    float fps_timer = fps_clock.getElapsedTime().asSeconds();

    // Create and render game window.
    sf::RenderWindow window(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), Globals::SCREEN_TITLE);
    window.setFramerateLimit(Globals::FRAME_RATE);

    // Load sounds
    SoundFx shoot_snd(Globals::SOUNDS_PATH + "shoot_laser.wav");
    SoundFx invader_death_snd(Globals::SOUNDS_PATH + "invader_death.wav");
    SoundFx invader_step1_snd(Globals::SOUNDS_PATH + "invader_step1.wav");
    SoundFx invader_step2_snd(Globals::SOUNDS_PATH + "invader_step2.wav");
    SoundFx invader_step3_snd(Globals::SOUNDS_PATH + "invader_step3.wav");
    SoundFx invader_step4_snd(Globals::SOUNDS_PATH + "invader_step4.wav");

    // Load spritesheet
    sf::Image spritesheet = Game::load_sprites(Globals::SPRITES_PATH + "invader_sprites.png");

    // Create Invaders!
    InvaderFormation invaders(window, spritesheet, Globals::SCREEN_WIDTH, invader_death_snd, invader_step1_snd, invader_step2_snd, invader_step3_snd, invader_step4_snd);

    // Create shields
    ShieldWall shields(window, spritesheet, Globals::SCREEN_WIDTH);

    // Create Core Cannon (player)
    CoreCannon cannon = CoreCannon(spritesheet, Globals::SCREEN_WIDTH, Globals::SCREEN_WIDTH / 2);
    
    // Create player laser
    PlayerLaser player_laser;
    
    // Create "Earth" (best name I could come up with
    // for the line at bottom of the screen)
    Earth earth(Globals::SCREEN_WIDTH);
    

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            cannon.move(1);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            cannon.move(-1);

        // Shoot laser
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player_laser.isShooting())
        {
            sf::Vector2f cannonpos = cannon.getSprite().getPosition();
            player_laser.shoot(cannonpos.x, cannonpos.y);
            shoot_snd.play();
        }

        /* Update objects */
        invaders.move();
        player_laser.move();

        invaders.checkHit(player_laser);
        shields.handleCollisions(player_laser);

        /* Display window and draw objects */
        Game::draw_objects(window, invaders, shields, cannon, player_laser, earth);

        Game::updateFPS(window, fps_clock, fps_timer);
    }
}
