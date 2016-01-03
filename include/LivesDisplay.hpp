#ifndef LIVESDISPLAY_H
#define LIVESDISPLAY_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Textures.hpp"

class LivesDisplay
{
private:
    static constexpr unsigned X = 0;
    static constexpr unsigned Y = 685;

    static constexpr unsigned LIVES_START = 3;

    // A sprite is made for each life left so it can be displayed.
    std::vector<sf::Sprite*> cannons;

    //Current number of lives left.
    unsigned lives;
    
    Textures &textures;

public:
    LivesDisplay(Textures &textures);
    ~LivesDisplay();
    unsigned getLives() const { return this->lives; }

    void reset();

    void removeLife();
    void addLife();
    void setLives(const unsigned num);
    void draw(sf::RenderWindow &window);

};

#endif
