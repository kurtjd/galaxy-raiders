#include <sstream>
#include "../inc/game.hpp"
#include "../inc/globals.hpp"

void Game::handle_events(sf::Window &window)
{
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
}

void Game::real_time_key(CoreCannon &cannon, PlayerLaser &player_laser)
{
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
    }
}

void Game::draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser)
{
    if (laser.isShooting())
        window.draw(laser.getShape());
}

void Game::update_objects(CoreCannon &cannon, PlayerLaser &player_laser, UFO &ufo, InvaderFormation &invaders, ShieldWall &shields, unsigned &game_score)
{
    Game::real_time_key(cannon, player_laser);
    player_laser.move();
    ufo.update(player_laser, game_score);
    invaders.update(player_laser, game_score);
    shields.handleCollisions(player_laser, invaders.getLasers());
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
