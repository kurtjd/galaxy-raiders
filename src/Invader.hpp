#ifndef invader_H
#define invader_H

#include <SFML/Graphics.hpp>

class Invader
{
private:
    static const int SPEED = 5; // How far the invader moves each step

    sf::Image spritesheet;

    int move_dir; // 1 is right, -1 is left, 0 is not moving

protected:
   // Invaders have 2 frames in their animation
    sf::Texture frame1_txtr;
    sf::Texture frame2_txtr;
    sf::Sprite sprite;
    
    unsigned score_value; // How many points the invader is worth when killed

    // Load textures for each frame given a rectangle containing location of texture on spritesheet
    void setTextures(sf::IntRect frame1, sf::IntRect frame2);

public:
    Invader(sf::Image &spritesheet);
    sf::Sprite& getSprite(){ return this->sprite; }
    unsigned getScoreValue(){ return this->score_value; }

};

#endif
