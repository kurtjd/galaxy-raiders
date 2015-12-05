#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H
#include <SFML/Graphics.hpp>

class PlayerBullet
{
private:
    static const int SPEED = 10;
    sf::RectangleShape bullet;
    bool is_shooting;

public:
    PlayerBullet();
    sf::RectangleShape& getShape(){ return this->bullet; }
    bool isShooting(){ return this->is_shooting; }

    // Places the bullet at given cooridnates (usually player ship)
    void placeAt(unsigned x, unsigned y);

    // Begins the shooting movement
    void shoot(unsigned startx, unsigned starty);

    // Bullet moves upwards after shot
    void move();

};

#endif
