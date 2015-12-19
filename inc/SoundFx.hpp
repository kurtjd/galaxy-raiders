#ifndef SOUNDFX_H
#define SOUNDFX_H

#include <string>
#include <SFML/Audio.hpp>

/* A simple helper class for SFML audio. */

class SoundFx
{
private:
    sf::Sound sound;
    sf::SoundBuffer buffer;

public:
    SoundFx(std::string filename);
    sf::SoundSource::Status getStatus(){ return sound.getStatus(); }
    void play(bool loop = false);
    void pause();
    void stop();
    void setVolume(float volume);

};

#endif
