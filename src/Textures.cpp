#include <string>
#include "../inc/globals.hpp"
#include "../inc/Textures.hpp"

sf::Image Textures::loadSprites(const std::string img)
{
    sf::Image ss;
    ss.loadFromFile(img);
    return ss;
}

Textures::Textures()
{
    this->spritesheet = this->loadSprites(Globals::SPRITES_PATH + "invader_sprites.png");

    sf::IntRect UFO_RECT(382, 33, 86, 38);
    this->UFO.loadFromImage(this->spritesheet, UFO_RECT);
    
    sf::IntRect UFO_MENU_RECT(318, 95, 87, 38);
    this->UFO_MENU.loadFromImage(this->spritesheet, UFO_MENU_RECT);

    sf::IntRect LARGE_INV_1_RECT(257, 35, 45, 35);
    sf::IntRect LARGE_INV_2_RECT(315, 35, 45, 35);
    this->LARGE_INV_1.loadFromImage(this->spritesheet, LARGE_INV_1_RECT);
    this->LARGE_INV_2.loadFromImage(this->spritesheet, LARGE_INV_2_RECT);

    sf::IntRect MEDIUM_INV_1_RECT(126, 35, 41, 35);
    sf::IntRect MEDIUM_INV_2_RECT(186, 35, 45, 35);
    this->MEDIUM_INV_1.loadFromImage(this->spritesheet, MEDIUM_INV_1_RECT);
    this->MEDIUM_INV_2.loadFromImage(this->spritesheet, MEDIUM_INV_2_RECT);

    sf::IntRect SMALL_INV_1_RECT(6, 35, 30, 35);
    sf::IntRect SMALL_INV_2_RECT(64, 35, 30, 35);
    this->SMALL_INV_1.loadFromImage(this->spritesheet, SMALL_INV_1_RECT);
    this->SMALL_INV_2.loadFromImage(this->spritesheet, SMALL_INV_2_RECT);

    sf::IntRect INVADER_DEATH_RECT(555, 107, 48, 30);
    this->INVADER_DEATH.loadFromImage(this->spritesheet, INVADER_DEATH_RECT);

    sf::IntRect SHIELD_RECT(562, 13, 80, 59);
    this->SHIELD.loadFromImage(this->spritesheet, SHIELD_RECT);

    sf::IntRect CORECANNON_RECT(492, 40, 48, 30);
    sf::IntRect CORECANNON_DEATH_1_RECT(421, 104, 54, 29);
    sf::IntRect CORECANNON_DEATH_2_RECT(485, 104, 55, 29);
    this->CORECANNON.loadFromImage(this->spritesheet, CORECANNON_RECT);
    this->CORECANNON_DEATH_1.loadFromImage(this->spritesheet, CORECANNON_DEATH_1_RECT);
    this->CORECANNON_DEATH_2.loadFromImage(this->spritesheet, CORECANNON_DEATH_2_RECT);

    sf::IntRect EXPLOSION_RECT(283, 110, 16, 20);
    this->EXPLOSION.loadFromImage(this->spritesheet, EXPLOSION_RECT);
}
