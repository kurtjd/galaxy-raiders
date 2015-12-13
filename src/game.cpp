#include <sstream>
#include "../inc/game.hpp"
#include "../inc/globals.hpp"

sf::Image Game::load_sprites(std::string img)
{
    sf::Image spritesheet;
    spritesheet.loadFromFile(img);
    return spritesheet;
}

void Game::draw_player_laser(sf::RenderWindow &window, PlayerLaser &laser)
{
    if (laser.isShooting())
        window.draw(laser.getShape());
}

void Game::draw_objects(sf::RenderWindow &window, InvaderFormation &invaders, ShieldWall &shields, CoreCannon &cannon, PlayerLaser &playerlaser, Earth &earth)
{
    window.clear(Globals::BG_COLOR);
    invaders.draw();
    shields.draw();
    window.draw(cannon.getSprite());
    Game::draw_player_laser(window, playerlaser);
    window.draw(earth.getShape());
    window.display();
}

void Game::updateFPS(sf::Window &window, sf::Clock &fps_clock, float &fps_timer)
{
    float fps = 1.0f / (fps_clock.getElapsedTime().asSeconds() - fps_timer);
    std::ostringstream title;
    title << Globals::SCREEN_TITLE << " - " << round(fps) << "fps";
    window.setTitle(title.str());
    fps_timer = fps_clock.getElapsedTime().asSeconds();
}
