#ifndef SOUNDFX_H
#define SOUNDFX_H

#include <string>
#include <SFML/Audio.hpp>

class SoundFx
{
private:
    sf::Sound sound;
    sf::SoundBuffer buffer;

public:
    SoundFx(std::string filename);
    void play();

};

#endif
