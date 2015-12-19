#include "../inc/Shield.hpp"

Shield::Shield(Textures &textures, const int xpos, const int ypos)
{
    this->img = textures.SHIELD.copyToImage();
    this->texture.loadFromImage(img);
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(xpos, ypos);
}

void Shield::handleCollide(PlayerLaser &player_laser, Lasers &invader_lasers)
{
    // TODO: Make code DRYer by figuring out a way to not repeat pixel FOR loop.

    sf::FloatRect shield_rect = this->sprite.getGlobalBounds();
    unsigned xpos = this->sprite.getPosition().x;
    unsigned ypos = this->sprite.getPosition().y;
    unsigned width = shield_rect.width;
    unsigned height = shield_rect.height;

    // Check for invader laser collision
    for (auto& laser : invader_lasers)
    {
        // First check if laser rect intersects with shield rect
        if (laser->checkCollide(shield_rect))
        {
            // Check to see if pixel collides with any Invader lasers.
            // Only true if hit green pixel
            for (unsigned x = xpos; x < (xpos + width); ++x)
            {
                for (unsigned y = ypos; y < (ypos + height); ++y)
                {
                    // Subtract xpos and ypos because the Image uses its own local coordinates
                    sf::Color pixel = this->img.getPixel(x - xpos, y - ypos);

                    if (pixel.g > 0 && laser->checkCollide(x, y))
                    {
                        laser->remove();
                        this->damageShield(x - xpos, y - ypos, laser->getDmg());
                        break; // Don't need to keep looking after first hit.
                    }
                }
            }
        }
    }

    // Check to see if pixel collides with player laser.
    sf::FloatRect player_laser_rect = player_laser.getShape().getGlobalBounds();
    if (player_laser_rect.intersects(shield_rect))
    {
        // Check to see if pixel collides with any Invader lasers.
        // Only true if hit green pixel
        for (unsigned x = xpos; x < (xpos + width); ++x)
        {
            for (unsigned y = ypos; y < (ypos + height); ++y)
            {
                // Subtract xpos and ypos because the Image uses its own local coordinates
                sf::Color pixel = this->img.getPixel(x - xpos, y - ypos);
                if (pixel.g > 0 && player_laser_rect.contains(x, y))
                {
                    this->damageShield(x - xpos, y - ypos, player_laser.getDmg());
                    player_laser.stop();
                }
            }
        }
    }
}

void Shield::handleCollideInvaders(InvaderFormation &invaders)
{
    sf::FloatRect shield_rect = this->sprite.getGlobalBounds();
    unsigned xpos = this->sprite.getPosition().x;
    unsigned ypos = this->sprite.getPosition().y;
    unsigned width = shield_rect.width;
    unsigned height = shield_rect.height;

    // Check for invader invader collision
    for (auto& invader_row : invaders.getInvaders())
    {
        for (auto& invader : invader_row)
        {
            // First check if invader rect intersects with shield rect
            if (invader->getSprite().getGlobalBounds().intersects(shield_rect))
            {
                // Check to see if pixel collides with any Invaders.
                // Only true if hit green pixel
                for (unsigned x = xpos; x < (xpos + width); ++x)
                {
                    for (unsigned y = ypos; y < (ypos + height); ++y)
                    {
                        // Subtract xpos and ypos because the Image uses its own local coordinates
                        sf::Color pixel = this->img.getPixel(x - xpos, y - ypos);

                        // If pixels touch, 'remove' that pixel to simulate destruction.
                        if (pixel.g > 0 && invader->getSprite().getGlobalBounds().contains(x, y))
                            this->img.setPixel(x - xpos, y - ypos, sf::Color::Transparent);
                    }
                }
            }
        }
    }

    this->texture.update(img);
}

void Shield::damageShield(int x, int y, const int dmg)
{
    int oldx = x;
    int oldy = y;

    for (x -= dmg; x < (oldx + dmg); ++x)
    {
        /* Cast x and y to unsigned to get rid of warning.
            They are int to begin with because they might be less than 0.
            However, short-cicuit evaluation ensures they won't be negative
            when compared to getSize() results. */
        if (x < 0 || static_cast<unsigned>(x) >= this->img.getSize().x)
            continue;

        for (y -= dmg; y < (oldy + dmg); ++y)
        {
            if (y < 0 || static_cast<unsigned>(y) >= this->img.getSize().y)
                continue;

            this->img.setPixel(x, y, sf::Color::Transparent);
        }
    }
    
    this->texture.update(img);
}
