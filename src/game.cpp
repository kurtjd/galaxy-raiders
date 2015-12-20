#include <sstream>
#include "../inc/game.hpp"
#include "../inc/globals.hpp"

void Game::handle_events(sf::Window &window, UFO &ufo)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
                case sf::Keyboard::P:
                    pause(ufo);
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
        }
    }
}

void Game::real_time_key(CoreCannon &cannon, PlayerLaser &player_laser)
{
    // Move Core Cannon
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        cannon.move(1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        cannon.move(-1);

    // Shoot laser
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !cannon.isHit() && !player_laser.isShooting())
    {
        sf::Vector2f cannonpos = cannon.getSprite().getPosition();
        player_laser.shoot(cannonpos.x, cannonpos.y);
    }
}

void Game::draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser)
{
    if (laser.isShooting())
        window.draw(laser.getShape());
}

void Game::update_objects(CoreCannon &cannon, PlayerLaser &player_laser, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields, LivesDisplay &lives_disp, unsigned &game_score)
{
    // Don't do anything if paused.
    if (Globals::GAME_STATE == Globals::States::PAUSED)
        return;

    if (Globals::GAME_STATE != Globals::States::PLAYER_KILLED)
    {
        Game::real_time_key(cannon, player_laser);
        player_laser.move();
        ufo.update(player_laser, game_score);
        invaders.update(player_laser, game_score);
        shields.handleCollisions(player_laser, invaders.getLasers(), invaders);
    }

    cannon.update(invaders, player_laser, ufo, lives_disp);
}

void Game::draw_text(sf::RenderWindow &window, const std::string msg, const unsigned x, const unsigned y, sf::Color color, unsigned size)
{
    sf::Font font;
    font.loadFromFile(Globals::FONTS_PATH + "space_invaders.ttf");

    sf::Text text;
    text.setFont(font);
    text.setString(msg);
    text.setCharacterSize(size);
    text.setColor(color);
    text.setPosition(x, y);

    window.draw(text);
}

void Game::draw_objects(sf::RenderWindow &window, ScoreDisplay &score_disp, LivesDisplay &lives_disp, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields, CoreCannon &cannon, PlayerLaser &playerlaser, Earth &earth)
{
    window.clear(Globals::BG_COLOR);
    score_disp.draw(window);
    ufo.draw(window);
    invaders.draw();
    invaders.drawLasers();
    shields.draw();
    window.draw(cannon.getSprite());
    Game::draw_player_laser(window, playerlaser);
    window.draw(earth.getSprite());
    lives_disp.draw(window);
    window.display();
}

void Game::updateFPS(sf::Window &window, const sf::Clock &fps_clock, float &fps_timer)
{
    float fps = 1.0f / (fps_clock.getElapsedTime().asSeconds() - fps_timer);
    std::ostringstream title;
    title << Globals::SCREEN_TITLE << " - " << round(fps) << "fps";
    window.setTitle(title.str());
    fps_timer = fps_clock.getElapsedTime().asSeconds();
}

void Game::pause(UFO &ufo)
{
    // Don't attempt to pause game if player is in middle of death.
    if (Globals::GAME_STATE == Globals::States::PLAYER_KILLED)
        return;

    if (Globals::GAME_STATE == Globals::States::PAUSED)
        Globals::GAME_STATE = Globals::States::PLAY;
    else
        Globals::GAME_STATE = Globals::States::PAUSED;

    ufo.pause();
}

void Game::handle_player_kill(InvaderFormation &invaders, PlayerLaser &player_laser, UFO &ufo, LivesDisplay &lives_disp)
{
    invaders.removeLasers();
    player_laser.stop();
    ufo.pause();
    lives_disp.removeLife();
    Globals::GAME_STATE = Globals::States::PLAYER_KILLED;
}
