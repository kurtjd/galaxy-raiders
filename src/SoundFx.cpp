#include <SFML/Audio.hpp>
#include "../inc/SoundFx.hpp"

SoundFx::SoundFx(std::string filename)
{
   this->buffer.loadFromFile(filename);
   this->sound.setBuffer(this->buffer);
}

void SoundFx::play()
{
    this->sound.play();
}
