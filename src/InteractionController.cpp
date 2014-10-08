#include "InteractionController.h"

#include "Simulation.h"

InteractionController::InteractionController(Simulation & simulation)
    : sim(simulation)
{}

InteractionController&
InteractionController::action1(std::tuple<float, float> targetPoint)
{
    using std::get;

    auto gridpos = sim.grid->getNearestNode(targetPoint);
    auto pulse = Gesture::RadialPulse{get<0>(gridpos), get<1>(gridpos), 3.0, 0.4};
    perturber.enqueue(pulse);

    return *this;
}
