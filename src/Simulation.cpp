#include "Simulation.h"

#include <boost/array.hpp>
#include <boost/multi_array.hpp>


Simulation::Simulation(std::shared_ptr<GridData> grid, float time_step, float c)
    : grid(grid)
    , time_step(time_step)
    , c(c)
{
    reset();
}


void Simulation::reset()
{
    tick_counter = 0;

    grid->fill(0.0);

    history.clear();
    history.push_front(*grid);
    history.push_front(*grid);
    history.push_front(*grid);
}


void Simulation::advanceOneTick()
{
    boost::array<size_t, 3> grid_shape;
    std::copy_n(grid->data.shape(), 3, grid_shape.begin());


    boost::multi_array<double, 3> spatial_laplacian(grid_shape);

    for(size_t i = 0; i < grid_shape[0]; ++i) {
        for(size_t j = 0; j < grid_shape[1]; ++j) {
            for(size_t k = 0; k < grid_shape[2]; ++k)
            {
                spatial_laplacian[i][j][k] = ((i > 0) ? grid->data[i-1][j][k] : 0)
                                           + ((j > 0) ? grid->data[i][j-1][k] : 0)
                                           + ((i+1 < grid_shape[0]) ? grid->data[i+1][j][k] : 0)
                                           + ((j+1 < grid_shape[1]) ? grid->data[i][j+1][k] : 0)
                                           - 4 * grid->data[i][j][k];
            }
        }
    }


    boost::multi_array<double, 3> next_grid(grid_shape);

    for(size_t i = 0; i < grid_shape[0]; ++i) {
        for(size_t j = 0; j < grid_shape[1]; ++j) {
            for(size_t k = 0; k < grid_shape[2]; ++k)
            {
                next_grid[i][j][k] = 0.5 * ( -(time_step/c)*(time_step/c) * spatial_laplacian[i][j][k]
                                             - 5 * history[0].data[i][j][k]
                                             + 4 * history[1].data[i][j][k]
                                             -     history[2].data[i][j][k]
                                            );
            }
        }
    }

    history.push_front(*grid);
    history.pop_back();

    grid->data = next_grid;
    ++tick_counter;
}
