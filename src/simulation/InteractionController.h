#ifndef INTERACTIONCONTROLLER_H
#define INTERACTIONCONTROLLER_H

#include <tuple>

#include "Perturbator.h"

class Simulation;


class InteractionController
{
    Simulation const& sim;
    Perturbator perturber;

public:
    InteractionController(Simulation&);

    InteractionController&
    action1(std::tuple<float,float> targetPoint);

    auto getInteractivityFilter() -> Perturbator& { return perturber; }
};


#endif // INTERACTIONCONTROLLER_H
