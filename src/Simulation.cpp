#include "Simulation.h"

#include <cstdio>
#include <cmath>
#include <array>

#include <boost/multi_array.hpp>

#include "BiFlattener.hpp"

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

Simulation::Simulation(std::shared_ptr<Grid> grid, float time_step, float c)
    : grid(grid)
    , time_step(time_step)
    , c(c)
    , interactor(*this)
{
    reset();
    prepareEquationsLU();
}


void Simulation::reset()
{
    tick_counter = 0;

    grid->fill(0.0);

    history.clear();
    history.push_front(grid->data);
    history.push_front(grid->data);
    history.push_front(grid->data);

    auto initial_edge_pulse = [this](Grid::data_type& grid) {
        if(tick_counter == 0) {
            for(size_t i = 0; i < grid.shape()[1]; ++i) {
                grid[1][i][0] = 0.2 * c * c;
            }
        }
    };

    auto edge_fixer = [](Grid::data_type& grid) {
        size_t m = grid.shape()[0];
        for(size_t i = 0; i < grid.shape()[1]; ++i) {
            grid[m-1][i][0] = 0.0;
            grid[0][i][0] = 0.0;
//            grid[m-1][i][1] = 0.0;
        }
    };

    struct dissipation {
        double k;
        explicit dissipation(double k) : k(k) {}
        void operator() (Grid::data_type& grid) {
            for(auto row: grid) {
                for(auto elem: row) {
                    elem[0] *= k;
                    elem[1] *= k;
                }
            }
        }
    };

    filters.push_back(initial_edge_pulse);
    filters.push_back(edge_fixer);
//    filters.push_back(dissipation(0.99));
}


void Simulation::advanceOneTick()
{
    auto next_grid = solveImplicitStep();

    for(auto& filter: filters) {
        filter(next_grid);
    }

    grid->data = std::move(next_grid); // this should happen sort of atomically

#if 0
    using boost::indices;
    printf("displacement field, x:\n");
    printFloatMatrix(grid->data[ indices [i_all] [i_all] [0] ]);
    printf("\n");
#endif

    history.push_front(grid->data);
    history.pop_back();

    ++tick_counter;
}


auto Simulation::solveExplicitStep() -> Grid::data_type {
    boost::multi_array<double, 3> spatial_laplacian(grid->shape);

    for(size_t i = 0; i < grid->shape[0]; ++i) {
        for(size_t j = 0; j < grid->shape[1]; ++j) {
            for(size_t k = 0; k < grid->shape[2]; ++k)
            {
                spatial_laplacian[i][j][k] = ((i > 0) ? grid->data[i-1][j][k] : 0)
                                           + ((j > 0) ? grid->data[i][j-1][k] : 0)
                                           + ((i+1 < grid->shape[0]) ? grid->data[i+1][j][k] : 0)
                                           + ((j+1 < grid->shape[1]) ? grid->data[i][j+1][k] : 0)
                                           - 4 * grid->data[i][j][k];
            }
        }
    }

    boost::multi_array<double, 3> result(grid->shape);

    double r = pow(c * time_step / grid->grid_step, 2);
    for(size_t i = 0; i < grid->shape[0]; ++i) {
        for(size_t j = 0; j < grid->shape[1]; ++j) {
            for(size_t k = 0; k < grid->shape[2]; ++k)
            {
                result[i][j][k] = 0.5 * ( + r * spatial_laplacian[i][j][k]
                                          + 5 * history[0][i][j][k]
                                          - 4 * history[1][i][j][k]
                                          + 1 * history[2][i][j][k]
                                         );
            }
        }
    }

    return result; // move semantics!
}

auto Simulation::solveImplicitStep() -> Grid::data_type {
    int N = grid->shape[0] * grid->shape[1]; // total number of nodes in the grid

    BiFlattener<size_t> index_helper {grid->shape[0]};

    // fill the equation system's vector b
    Eigen::VectorXd b0(N);
    Eigen::VectorXd b1(N);
    for(size_t i = 0; i < grid->shape[0]; ++i) {
        for(size_t j = 0; j < grid->shape[1]; ++j) {
            int eqn = index_helper.flatten(i, j);
            b0[eqn] = 5 * history[0][i][j][0] - 4 * history[1][i][j][0] + history[2][i][j][0];
            b1[eqn] = 5 * history[0][i][j][1] - 4 * history[1][i][j][1] + history[2][i][j][1];
        }
    }

    // perform the decomposed matrix multiplication
    Eigen::VectorXd solution0 = equations_lu.solve(b0);
    Eigen::VectorXd solution1 = equations_lu.solve(b1);
    if(equations_lu.info() != Eigen::Success) {
        throw std::runtime_error("decomposed matrix multiplication failed");
    }

    // prepare result
    Grid::data_type result(grid->shape);
    for(int eqn = 0; eqn < N; ++eqn) {
        int i, j;
        std::tie(i, j) = index_helper.unflatten(eqn);
        result[i][j][0] = solution0[eqn];
        result[i][j][1] = solution1[eqn];
    }

    return result; // move semantics!
}

void Simulation::prepareEquationsLU() {
    double r = pow(c * time_step / grid->grid_step, 2);

    unsigned N = grid->shape[0] * grid->shape[1]; // total number of nodes in the grid

    BiFlattener<size_t> index_helper {grid->shape[0]};
    auto flatten = [&](size_t i, size_t j) { return index_helper.flatten(i, j); };

    equations.resize(N, N);
    for(size_t i = 0; i < grid->shape[0]; ++i) {
        for(size_t j = 0; j < grid->shape[1]; ++j) {
            int eqn = flatten(i, j);

            equations.insert(flatten(i, j), eqn) = (2 + 4 * r);

            if(i > 0)
                equations.insert(flatten(i-1, j), eqn) = -r;

            if(i + 1 < grid->shape[0])
                equations.insert(flatten(i+1, j), eqn) = -r;

            if(j > 0)
                equations.insert(flatten(i, j-1), eqn) = -r;

            if(j + 1 < grid->shape[1])
                equations.insert(flatten(i, j+1), eqn) = -r;
        }
    }
    equations.finalize();

    equations_lu.compute(equations);
    if(equations_lu.info() != Eigen::Success) {
        throw std::runtime_error("LU decomposition failed");
    }
}
