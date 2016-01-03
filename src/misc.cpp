#include <cstdlib>
#include "misc.hpp"

unsigned Misc::random(const unsigned low, const unsigned high)
{
    return (rand() % (high - low + 1)) + low;
}
