#ifndef PLAYERLASER_H
#define PLAYERLASER_H

#include <SFML/Graphics.hpp>

class PlayerLaser
{
private:
    static const unsigned WIDTH = 3;
    static const unsigned HEIGHT = 15;

    static const int SPEED = 10;
    sf::RectangleShape laser;
    bool is_shooting;

public:
    PlayerLaser();
    sf::RectangleShape& getShape(){ return this->laser; }
    bool isShooting(){ return this->is_shooting; }

    // Begins the shooting movement
    void shoot(unsigned startx, unsigned starty);

    // Laser moves upwards after shot
    void move();

    // Called to make the laser stop shooting
    void stop();

};

#endif
