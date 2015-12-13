#include "../inc/Shield.hpp"

Shield::Shield(sf::Image &spritesheet, int xpos): spritesheet(spritesheet)
{
    this->texture.loadFromImage(spritesheet, sf::IntRect(this->TXTR_X_START, this->TXTR_Y_START, this->TXTR_WIDTH, this->TXTR_HEIGHT));
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(xpos, this->Y_POS);
    this->img = texture.copyToImage();
}

void Shield::handleCollide(PlayerLaser &laser, Lasers &invader_lasers)
{
    unsigned xpos = this->sprite.getPosition().x;
    unsigned ypos = this->sprite.getPosition().y;
    unsigned width = this->sprite.getGlobalBounds().width;
    unsigned height = this->sprite.getGlobalBounds().height;

    for (unsigned x = xpos; x < (xpos + width); ++x)
    {
        for (unsigned y = ypos; y < (ypos + height); ++y)
        {
            // Subtract xpos and ypos because the Image uses its own local coordinates
            sf::Color pixel = this->img.getPixel(x - xpos, y - ypos);

            // Check to see if pixel collides with any Invader lasers.
            bool invader_laser_hit = false;
            for (auto& laser : invader_lasers)
            {
                if (laser->getSprite().getGlobalBounds().contains(x, y) && pixel.g > 0)
                {
                    invader_laser_hit = true;
                    laser->remove();
                    break; // Don't need to keep looking after first hit.
                }
            }

            // Only true if hit green pixel
            bool player_laser_hit = laser.getShape().getGlobalBounds().contains(x, y) && pixel.g > 0;
            if (invader_laser_hit || player_laser_hit)
            {
                this->damageShield(x - xpos, y - ypos);
                if (player_laser_hit)
                    laser.stop();
            }
        }
    }
}

void Shield::damageShield(int x, int y)
{
    int oldx = x;
    int oldy = y;

    for (x -= this->IMPACT_SIZE; x < (oldx + this->IMPACT_SIZE); ++x)
    {
        /* Cast x and y to unsigned to get rid of warning.
            They are int to begin with because they might be less than 0.
            However, short-cicuit evaluation ensures they won't be negative
            when compared to getSize() results. */
        if (x < 0 || static_cast<unsigned>(x) >= this->img.getSize().x)
            continue;

        for (y -= this->IMPACT_SIZE; y < (oldy + this->IMPACT_SIZE); ++y)
        {
            if (y < 0 || static_cast<unsigned>(y) >= this->img.getSize().y)
                continue;

            this->img.setPixel(x, y, sf::Color::Transparent);
        }
    }
    
    this->texture.update(img);
    this->sprite.setTexture(this->texture);
}
