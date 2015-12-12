#ifndef INVADERCOMMANDER_H
#define INVADERCOMMANDER_H

#include "InvaderFormation.hpp"

// The invisible, all-knowing "Commander" of the Space Invaders!
// Used to coordinate laser fire of the Invader formation
// Makes sense to be a class because there could theoretically be
// multiple Invader formations each with their own Commander
class InvaderCommander
{
private:
    InvaderFormation &invaders;

public:
    InvaderCommander();

};

#endif
