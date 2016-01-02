#ifndef INVADER_H
#define INVADER_H

#include <SFML/Graphics.hpp>
#include "Textures.hpp"

/* An individual Space Invader. */

class Invader
{
// This is up here because I like private members first,
// but this needs to be public and is used by a private member.
// The different types of Invaders
public: enum InvaderType { LARGE, MEDIUM, SMALL };

private:
    static constexpr unsigned HEIGHT = 35;
    static constexpr unsigned DEATH_TICK_MAX = 10; // How long death sprite should show
    static constexpr int SPEED = 10; // How far the invader moves each step

    // Invaders have 2 frames in their animation.
    // They are pointers instead of references because they can't be default initialized.
    sf::Texture *frame1_txtr;
    sf::Texture *frame2_txtr;
    sf::Texture *frame3_txtr;
    sf::Sprite sprite;

    InvaderType type;
    unsigned score_value; // How many points the invader is worth when killed
    int move_dir; // 1 is right, -1 is left, 0 is not moving
    bool is_dead;
    bool is_exploding;
    int frame_on; // Either 1 or 2

    unsigned death_tick; // Keep track of how long death sprite has shown

    unsigned lasers_on_screen;


    // Cycle through animation
    void flipFrame();

public:
    Invader(Textures &textures, const InvaderType type);
    sf::Sprite& getSprite() { return this->sprite; }
    static unsigned getHeight() { return Invader::HEIGHT; }
    unsigned getScoreValue() const { return this->score_value; }
    bool isDead() const { return this->is_dead; }
    bool isExploding() const { return this->is_exploding; }
    int getMoveDir() const { return this->move_dir; }
    unsigned getLasersOnScreen() const { return this->lasers_on_screen; }

    void reset(const unsigned x, const unsigned y);
    
    // Called when Invader is hit by bullet
    void die();

    // Called every movement tick
    void move();

    // The invader shifts down one row
    void dropDown(const unsigned shield_line);

    // The invader reverses its direction of movement
    void reverseDir();

    // Checks if Invader hit edge of screen
    bool checkHitEdge(const int screenw);
    
    // Increment death tick and hide once hit max
    void incDeathTick();

    void incLasersOnScreen() { ++this->lasers_on_screen; }
    void decLasersOnScreen() { --this->lasers_on_screen; }

};

#endif
