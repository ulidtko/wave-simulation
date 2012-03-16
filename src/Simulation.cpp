#include "Simulation.h"

#include <boost/array.hpp>
#include <boost/multi_array.hpp>

#include <cstdio>
#include <cmath>

auto static i_all = boost::multi_array_types::index_range(); // "all" index range


template<class M>
void printFloatMatrix(const M& matrix) {
    using std::printf;
    for(const auto& row : matrix) {
        for(const auto& elem : row) {
            printf("%5.3f ", elem);
        }
        printf("\n");
    }
}


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
#if 1
                spatial_laplacian[i][j][k] = ((i > 0) ? grid->data[i-1][j][k] : 0)
                                           + ((j > 0) ? grid->data[i][j-1][k] : 0)
                                           + ((i+1 < grid_shape[0]) ? grid->data[i+1][j][k] : 0)
                                           + ((j+1 < grid_shape[1]) ? grid->data[i][j+1][k] : 0)
                                           - 4 * grid->data[i][j][k];
#else
                spatial_laplacian[i][j][k] = - 1/12.0 * ((i > 1) ? grid->data[i-2][j][k] : 0.0)
                                             - 1/12.0 * ((j > 1) ? grid->data[i][j-2][k] : 0.0)
                                             +  4/3.0 * ((i > 0) ? grid->data[i-1][j][k] : 0.0)
                                             +  4/3.0 * ((j > 0) ? grid->data[i][j-1][k] : 0.0)
                                             -    5.0 * grid->data[i][j][k]
                                             +  4/3.0 * ((i+1 < grid_shape[0]) ? grid->data[i+1][j][k] : 0.0)
                                             +  4/3.0 * ((j+1 < grid_shape[1]) ? grid->data[i][j+1][k] : 0.0)
                                             - 1/12.0 * ((i+2 < grid_shape[0]) ? grid->data[i+2][j][k] : 0.0)
                                             - 1/12.0 * ((j+2 < grid_shape[1]) ? grid->data[i][j+2][k] : 0.0);
#endif
            }
        }
    }

#if 0
    using boost::indices;
    printf("displacement field, x:\n");
    printFloatMatrix(grid->data[ indices [i_all] [i_all] [0] ]);
    printf("\n");
#endif

#if 0
    using boost::indices;
    printf("spatial laplacian, x:\n");
    printFloatMatrix(spatial_laplacian[ indices [i_all] [i_all] [0] ]);
    printf("\n");
#endif


    boost::multi_array<double, 3> next_grid(grid_shape);

    for(size_t i = 0; i < grid_shape[0]; ++i) {
        for(size_t j = 0; j < grid_shape[1]; ++j) {
            for(size_t k = 0; k < grid_shape[2]; ++k)
            {
                next_grid[i][j][k] = 0.5 * ( +(time_step/c)*(time_step/c) * spatial_laplacian[i][j][k]
                                             + 5 * history[0].data[i][j][k]
                                             - 4 * history[1].data[i][j][k]
                                             + 1 * history[2].data[i][j][k]
                                            );
            }
        }
    }

    grid->data = next_grid;

    history.push_front(*grid);
    history.pop_back();

    ++tick_counter;
}
