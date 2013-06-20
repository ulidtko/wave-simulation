#ifndef SIMULATION_H
#define SIMULATION_H

#include <deque>
#include <memory>

#include <Eigen/Sparse>
#include <Eigen/UmfPackSupport>

#include "GridData.h"


class Simulation
{
public:
    explicit Simulation(std::shared_ptr<Grid> grid,
                        float time_step = 0.01,
                        float c = 10.0);

    void reset();
    void advanceOneTick();

    typedef std::function<void(Grid::data_type&)> Filter;
    std::vector<Filter> filters;

private:
    std::shared_ptr<Grid> grid;
    float time_step;
    int tick_counter;
    float c; // speed of wave propagation

    std::deque<Grid::data_type> history;

private:
    Eigen::SparseMatrix<double> equations;
    Eigen::UmfPackLU<decltype(equations)> equations_lu;

    void prepareEquationsLU();

private:
    auto solveExplicitStep() -> Grid::data_type;
    auto solveImplicitStep() -> Grid::data_type;
};

#endif // SIMULATION_H
