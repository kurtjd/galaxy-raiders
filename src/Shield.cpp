#include "../inc/Shield.hpp"

Shield::Shield(sf::Image &spritesheet, int xpos): spritesheet(spritesheet)
{
    this->texture.loadFromImage(spritesheet, sf::IntRect(this->TXTR_X_START, this->TXTR_Y_START, this->TXTR_WIDTH, this->TXTR_HEIGHT));
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(xpos, this->Y_POS);
    this->img = texture.copyToImage();
}

bool Shield::checkCollide(PlayerLaser &laser)
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

            // Only true if hit green pixel
            if (laser.getShape().getGlobalBounds().contains(x, y) && pixel.g > 0)
            {
                // Eh, probably shouldn't have side-effect in bool method, but it's too easy
                this->damageShield(x - xpos, y - ypos);
                return true;
            }
        }
    }

    return false;
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
