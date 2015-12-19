#include "../inc/SoundFx.hpp"

SoundFx::SoundFx(std::string filename)
{
   this->buffer.loadFromFile(filename);
   this->sound.setBuffer(this->buffer);
}

void SoundFx::play(bool loop)
{
    this->sound.setLoop(loop);
    this->sound.play();
}

void SoundFx::stop()
{
    this->sound.stop();
}

void SoundFx::setVolume(float volume)
{
    this->sound.setVolume(volume);
}
