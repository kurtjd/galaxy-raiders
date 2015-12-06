#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "SoundFx.hpp"
#include "Invader.hpp"
#include "Shield.hpp"
#include "CoreCannon.hpp"
#include "PlayerLaser.hpp"
#include "Earth.hpp"

/* Helpers */
typedef std::vector<Invader*> InvaderRow;
typedef std::vector<InvaderRow> InvaderFormation;
typedef std::vector<Shield*> ShieldWall;

/* Globals */
unsigned move_tick_change = 5;

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

// Load a sound into buffer
void load_sound(sf::SoundBuffer &buffer, std::string filename)
{
    buffer.loadFromFile(filename);
}

// Play a sound
void play_sound(sf::Sound &sound, sf::SoundBuffer &buffer)
{
    sound.setBuffer(buffer);
    sound.play();
}

// Creates an Image object to be used as a texture for sprites.
sf::Image load_sprites(std::string img)
{
    sf::Image spritesheet;
    spritesheet.loadFromFile(img);
    return spritesheet;
}

// Create Invader formation
void init_invaders(sf::Image &spritesheet, InvaderFormation &invaders)
{
    // Vector for each row in the formation
    InvaderRow small_invaders;
    InvaderRow medium_invaders1;
    InvaderRow medium_invaders2;
    InvaderRow large_invaders1;
    InvaderRow large_invaders2;

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
void del_invaders(InvaderFormation &invaders)
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
void draw_invaders(sf::RenderWindow &window, InvaderFormation &invaders)
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
void init_shields(sf::Image &spritesheet, ShieldWall &shields)
{
    // Create shields on the heap so they don't go out of scope.
    // This loop creates 4 shields across the screen.
    // 97 is start point, -5 is to stop part of 5th shield from drawing at edge
    for (unsigned i = 97; i < SCREEN_WIDTH - 5; i += 175)
        shields.push_back(new Shield(spritesheet, i));
}

// Remove shields from memory
void del_shields(ShieldWall &shields)
{
    for (unsigned i = 0; i < shields.size(); ++i)
        delete shields[i];

    shields.clear();
}

// Draws the shields to the screen
void draw_shields(sf::RenderWindow &window, ShieldWall &shields)
{
    for (unsigned i = 0; i < shields.size(); ++i)
        window.draw(shields[i]->getSprite());
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
    draw_invaders(window, invaders);
    draw_shields(window, shields);
    window.draw(cannon.getSprite());
    draw_player_laser(window, playerlaser);
    window.draw(earth.getShape());
    window.display();
}

// Increase speed, drop down, and reverse direction!
void shift_formation(InvaderFormation &invaders, unsigned &move_tick_max)
{
    // Slow down move tick change if getting max is getting
    // close to 0, and don't go any lower than 1 so they
    // don't stop moving.
    if (move_tick_max > 5)
        move_tick_max -= move_tick_change;
    else if (move_tick_max > 1)
        --move_tick_max;

    for (unsigned i = 0; i < invaders.size(); ++i)
    {
        for (unsigned j = 0; j < invaders[i].size(); ++j)
        {
            Invader *invader = invaders[i][j];
            invader->dropDown();
            invader->reverseDir();
        }
    }
}

// Move the Invader formation
void invaders_move(InvaderFormation &invaders, unsigned &move_tick_max)
{
    bool hit_edge = false;
    for (unsigned i = 0; i < invaders.size(); ++i)
    {
        for (unsigned j = 0; j < invaders[i].size(); ++j)
        {
            Invader *invader = invaders[i][j];

            invader->move();
            if (invader->checkHitEdge(SCREEN_WIDTH))
                hit_edge = true;
        }
    }

    if (hit_edge)
        shift_formation(invaders, move_tick_max);
}

// Check collision between player laser and Invaders
void check_invader_hit(InvaderFormation &invaders, PlayerLaser &laser, SoundFx &invader_death_snd)
{
    for (unsigned i = 0; i < invaders.size(); ++i)
    {
        for (unsigned j = 0; j < invaders[i].size(); ++j)
        {
            Invader *invader = invaders[i][j];
            if (!invader->isDead() && invader->getSprite().getGlobalBounds().intersects(laser.getShape().getGlobalBounds()))
            {
                invader->die();
                invader_death_snd.play();
                laser.stop();
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
    InvaderFormation invaders;
    init_invaders(spritesheet, invaders);

    // Create shields
    ShieldWall shields;
    init_shields(spritesheet, shields);

    // Create Core Cannon (player)
    CoreCannon cannon = CoreCannon(spritesheet, SCREEN_WIDTH / 2);
    
    // Create player laser
    PlayerLaser player_laser;
    
    // Create "Earth" (best name I could come up with
    // for the line at bottom of the screen)
    Earth earth(SCREEN_WIDTH);

    // When move_tick hits move_tick_max, the formation moves
    // move_tick_max is lowered every time formation hits edge of screen
    unsigned move_tick = 0;
    unsigned move_tick_max = FRAME_RATE / 1.5;
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

        // Shoot laser
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player_laser.isShooting())
        {
            sf::Vector2f cannonpos = cannon.getSprite().getPosition();
            player_laser.shoot(cannonpos.x, cannonpos.y);

            shoot_snd.play();
        }

        /* Update objects */
        ++move_tick;
        if (move_tick == move_tick_max)
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

            move_tick = 0;
            invaders_move(invaders, move_tick_max);

            ++step_on;
            if (step_on > 4)
                step_on = 1;
        }

        check_invader_hit(invaders, player_laser, invader_death_snd);
        player_laser.move();

        /* Display window and draw objects */
        draw_objects(window, invaders, shields, cannon, player_laser, earth);

        //updateFPS(window, fps_clock, fps_timer);
    }
}
