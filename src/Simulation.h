#ifndef SIMULATION_H
#define SIMULATION_H

#include <deque>
#include <memory>

#include "GridData.h"

class Simulation
{
public:
    explicit Simulation(std::shared_ptr<Grid> grid,
                        float time_step = 0.01,
                        float c = 10.0);

    void reset();
    void advanceOneTick();

private:
    std::shared_ptr<Grid> grid;
    float time_step;
    int tick_counter;
    float c; // speed of wave propagation

    std::deque<Grid::data_type> history;

private:
    auto solveExplicitStep() -> Grid::data_type;
    auto solveImplicitStep() -> Grid::data_type;
};

#endif // SIMULATION_H
