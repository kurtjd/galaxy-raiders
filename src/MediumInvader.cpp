#include <SFML/Graphics.hpp>
#include "MediumInvader.hpp"

MediumInvader::MediumInvader(sf::Image &spritesheet): Invader(spritesheet)
{
    sf::IntRect frame1_rect(126, 35, 41, 30);
    sf::IntRect frame2_rect(186, 35, 45, 30);
    this->setTextures(frame1_rect, frame2_rect);
    this->sprite.setTexture(this->frame1_txtr);

    // Put the point of origin in center of invader.
    this->sprite.setOrigin(this->frame1_txtr.getSize().x / 2, this->frame1_txtr.getSize().y / 2);

    this->score_value = 20; // According to arcade game
}
