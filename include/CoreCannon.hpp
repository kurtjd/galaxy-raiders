#ifndef PLAYERcannon_H
#define PLAYERcannon_H

#include <SFML/Graphics.hpp>
#include "SoundFx.hpp"
#include "Textures.hpp"
#include "InvaderFormation.hpp"
#include "Explosions.hpp"

/* The player's ship. */

class CoreCannon
{
private:
    SoundFx &killed_sound;

    const unsigned START_X;
    static constexpr unsigned Y = 623;

    static constexpr int SPEED = 5; // Movement speed of cannon
    static constexpr unsigned DEATH_TICK_MAX = 50;
    static constexpr unsigned FRAME_TICK_MAX = 3;

    Textures &textures;
    sf::Sprite sprite;

    unsigned frame_on;
    bool hit;
    unsigned death_tick;
    unsigned frame_tick;

    void flipFrame();

public:
    CoreCannon(Textures &textures, SoundFx &killed_sound, const int startx);
    bool isHit() const { return this->hit; }

    void reset();
    void move(const int dir);
    const sf::Sprite& getSprite() const { return this->sprite; }
    unsigned getX() const { return this->sprite.getPosition().x; }
    unsigned getWidth() const { return this->getSprite().getGlobalBounds().width; }
    void die(InvaderFormation &invaders, PlayerLaser &player_laser, UFO &ufo, Explosions &explosions);
    void handleHit(InvaderFormation &invaders, PlayerLaser &player_laser, UFO &ufo, Explosions &explosions);
    void update(InvaderFormation &invaders, PlayerLaser &player_laser, UFO &ufo, LivesDisplay &lives_disp, Explosions &explosions);

};

#endif
