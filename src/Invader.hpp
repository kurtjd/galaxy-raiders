#ifndef INVADER_H
#define INVADER_H

#include <SFML/Graphics.hpp>

class Invader
{
// This is up here because I like private members first,
// but this needs to be public and is used by a private member.
// The different types of Invaders
public: enum InvaderType { LARGE, MEDIUM, SMALL };

private:
    static const int SPEED = 5; // How far the invader moves each step

    // Invaders have 2 frames in their animation
    sf::Image spritesheet;
    sf::Texture frame1_txtr;
    sf::Texture frame2_txtr;
    sf::Sprite sprite;

    InvaderType type;
    unsigned score_value; // How many points the invader is worth when killed
    int move_dir; // 1 is right, -1 is left, 0 is not moving
    bool is_dead;

    // Load textures for each frame given a rectangle containing location of texture on spritesheet
    void setTextures(sf::IntRect frame1, sf::IntRect frame2);

public:
    Invader(sf::Image &spritesheet, InvaderType type);

    // Called when Invader is hit by bullet
    void die();

    sf::Sprite& getSprite(){ return this->sprite; }
    unsigned getScoreValue(){ return this->score_value; }
    bool isDead(){ return this->is_dead; }

};

#endif
