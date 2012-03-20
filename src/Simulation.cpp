#include "Simulation.h"

#include <cstdio>
#include <cmath>
#include <array>

#include <boost/multi_array.hpp>

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
}


void Simulation::advanceOneTick()
{
    auto next_grid = solveImplicitStep();

    grid->data = next_grid;

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

    history.push_front(grid->data);
    history.pop_back();

    ++tick_counter;
}


auto Simulation::solveExplicitStep() -> Grid::data_type {
    std::array<size_t,3> grid_shape;
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

    boost::multi_array<double, 3> result(grid_shape);

    for(size_t i = 0; i < grid_shape[0]; ++i) {
        for(size_t j = 0; j < grid_shape[1]; ++j) {
            for(size_t k = 0; k < grid_shape[2]; ++k)
            {
                result[i][j][k] = 0.5 * ( +(time_step/c)*(time_step/c) * spatial_laplacian[i][j][k]
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
    std::array<size_t,3> grid_shape;
    std::copy_n(grid->data.shape(), 3, grid_shape.begin());

    int shape0 = grid_shape[0]; // height
    int shape1 = grid_shape[1]; // width
    int N = shape0 * shape1; // total number of nodes in the grid

    auto flatten = [shape0](int i, int j) { return i + j * shape0; };
    auto unflatten = [shape0](int k) { return std::make_tuple(k % shape0, k / shape0); };

    // fill the equation system's vector b
    Eigen::VectorXd b0(N);
    Eigen::VectorXd b1(N);
    for(int i = 0; i < shape0; ++i) {
        for(int j = 0; j < shape1; ++j) {
            b0[flatten(i,j)] = 5 * history[0][i][j][0] - 4 * history[1][i][j][0] + history[2][i][j][0];
            b1[flatten(i,j)] = 5 * history[0][i][j][1] - 4 * history[1][i][j][1] + history[2][i][j][1];
        }
    }

    // call the solver
    Eigen::VectorXd solution0(N);
    Eigen::VectorXd solution1(N);
    if(!equations_lu.solve(b0, &solution0)) {
        throw std::runtime_error("Eigen::SparseLU<...>::solve() failed");
    }
    if(!equations_lu.solve(b1, &solution1)) {
        throw std::runtime_error("Eigen::SparseLU<...>::solve() failed");
    }

    // prepare result
    Grid::data_type result(grid_shape);
    for(int eqn = 0; eqn < N; ++eqn) {
        int i, j;
        std::tie(i, j) = unflatten(eqn);
        result[i][j][0] = solution0[eqn];
        result[i][j][1] = solution1[eqn];
    }

    return result; // move semantics!
}

void Simulation::prepareEquationsLU() {
    std::array<size_t,3> grid_shape;
    std::copy_n(grid->data.shape(), 3, grid_shape.begin());

    double r = pow(c * time_step / grid->grid_step, 2);

    size_t shape0 = grid_shape[0]; // height
    size_t shape1 = grid_shape[1]; // width
    unsigned N = shape0 * shape1; // total number of nodes in the grid

    auto flatten = [shape0](int i, int j) { return i + j * shape0; };
    auto unflatten = [shape0](int k) { return std::make_tuple(k % shape0, k / shape0); };

    equations.resize(N, N);
    for(size_t i = 0; i < grid_shape[0]; ++i) {
        for(size_t j = 0; j < grid_shape[1]; ++j) {
            int eqn = flatten(i, j);

            equations.insert(flatten(i, j), eqn) = (2 + 4 * r);

            if(i > 0)
                equations.insert(flatten(i-1, j), eqn) = -r;

            if(i + 1 < shape0)
                equations.insert(flatten(i+1, j), eqn) = -r;

            if(j > 0)
                equations.insert(flatten(i, j-1), eqn) = -r;

            if(j + 1 < shape1)
                equations.insert(flatten(i, j+1), eqn) = -r;
        }
    }
    equations.finalize();

    equations_lu.compute(equations);
    if(!equations_lu.succeeded()) {
        throw std::runtime_error("LU decomposition failed");
    }
}
