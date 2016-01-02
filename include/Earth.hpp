#ifndef EARTH_H
#define EARTH_H

#include <SFML/Graphics.hpp>

/* The little line at the bottom of the screen. Everything you are fighting for! */

class Earth
{
private:
    static constexpr unsigned HEIGHT = 2;
    const unsigned WIDTH;
    static constexpr unsigned X = 0;
    static constexpr unsigned Y = 680;
    static constexpr unsigned SPLASH_DMG = 5;

    sf::Image img;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Earth(const unsigned screenw);
    const sf::Sprite& getSprite() const { return this->sprite; }

    void reset();

    void destroy(const unsigned x);

};

#endif
