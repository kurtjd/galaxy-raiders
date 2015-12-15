#ifndef INVADERLASER_T
#define INVADERLASER_T

/* Implement the templated methods for InvaderLaser.
 * Seems really clunky, but don't know of another way to allow for multiple
 * sf::Rect types in a single method. */

template<typename T>
bool InvaderLaser::checkCollideNormLaser(const sf::Rect<T> rect) const
{
    if (rect.intersects(this->v_part.getGlobalBounds()) || rect.intersects(this->h_part.getGlobalBounds()))
        return true;

    return false;
}

template<typename T>
bool InvaderLaser::checkCollide(const sf::Rect<T> rect) const
{
    switch(this->type)
    {
    case InvaderLaser::NORMAL:
        return this->checkCollideNormLaser(rect);
        break;

    case InvaderLaser::POWERED:
        break;

    default:
        break;
    }

    return false; // Shouldn't get here...
}

#endif
