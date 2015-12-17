#include <ctime>
#include <SFML/Graphics.hpp>
#include "../inc/globals.hpp"
#include "../inc/misc.hpp"
#include "../inc/game.hpp"
#include "../inc/SoundFx.hpp"

int main()
{
    unsigned game_score = 0;

    srand(time(0));

    sf::Clock fps_clock;
    float fps_timer = fps_clock.getElapsedTime().asSeconds();

    sf::RenderWindow window(sf::VideoMode(Globals::SCREEN_WIDTH, Globals::SCREEN_HEIGHT), Globals::SCREEN_TITLE);
    window.setFramerateLimit(Globals::FRAME_RATE);

    SoundFx shoot_snd(Globals::SOUNDS_PATH + "shoot_laser.wav");
    SoundFx invader_death_snd(Globals::SOUNDS_PATH + "invader_death.wav");
    SoundFx invader_step1_snd(Globals::SOUNDS_PATH + "invader_step1.wav");
    SoundFx invader_step2_snd(Globals::SOUNDS_PATH + "invader_step2.wav");
    SoundFx invader_step3_snd(Globals::SOUNDS_PATH + "invader_step3.wav");
    SoundFx invader_step4_snd(Globals::SOUNDS_PATH + "invader_step4.wav");

    sf::Image spritesheet = Game::load_sprites(Globals::SPRITES_PATH + "invader_sprites.png");
    
    Earth earth(Globals::SCREEN_WIDTH);

    UFO ufo(spritesheet);

    InvaderFormation invaders(window, spritesheet, earth, Globals::SCREEN_WIDTH, game_score, invader_step1_snd, invader_step2_snd, invader_step3_snd, invader_step4_snd, invader_death_snd);

    ShieldWall shields(window, spritesheet, Globals::SCREEN_WIDTH);

    CoreCannon cannon(spritesheet, Globals::SCREEN_WIDTH, Globals::SCREEN_WIDTH / 2);
    
    PlayerLaser player_laser(shoot_snd);

    ScoreDisplay score_disp(game_score);

    LivesDisplay lives_disp(spritesheet);

    
    /* Begin game loop */
    while (window.isOpen())
    {
        Game::handle_events(window);
        Game::update_objects(cannon, player_laser, ufo, invaders, shields);
        Game::draw_objects(window, score_disp, lives_disp, ufo, invaders, shields, cannon, player_laser, earth);
        Game::updateFPS(window, fps_clock, fps_timer);
    }
}
