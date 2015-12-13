#include <cstdlib>
#include "../inc/misc.hpp"

unsigned Misc::random(unsigned low, unsigned high)
{
    return (rand() % (high - low + 1)) + low;
}
