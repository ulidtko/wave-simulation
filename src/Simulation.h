#ifndef SIMULATION_H
#define SIMULATION_H

#include <deque>
#include "GridData.h"

class Simulation
{
public:
    explicit Simulation(std::unique_ptr<GridData> grid,
                        float time_step = 0.01, float c = 10.0);

    void reset();
    void advanceOneTick();

private:
    std::unique_ptr<GridData> grid;
    float time_step;
    int tick_counter;
    float c; // speed of wave propagation

    std::deque<GridData> history;
};

#endif // SIMULATION_H
