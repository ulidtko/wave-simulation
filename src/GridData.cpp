#include "GridData.h"

#include <cmath>

using std::make_tuple;
using std::get;

Grid::Grid(float width, float height, float grid_step)
    : width(width)
    , height(height)
    , grid_step(grid_step)
{
    int width_cells = width / grid_step;
    int height_cells = height / grid_step;

    data_type::extent_gen extents;
    data.resize(extents[width_cells][height_cells][2]);
    std::copy_n(data.shape(), 3, shape.begin());
}


void Grid::fill(double value)
{
    for(auto d2 : data)
        for(auto d1 : d2)
            for(auto& el : d1)
            {
                el = value;
            }
}


tuple<double,double> Grid::getNodeOrigin(int i, int j) const {
    return make_tuple(i * grid_step, j * grid_step);
}


tuple<double,double> Grid::getNodePosition(int i, int j) const {
    return make_tuple(i * grid_step + data[i][j][0],
                      j * grid_step + data[i][j][1]);
}

tuple<int, int> Grid::getNearestNode(tuple<double, double> pos) const {
    return make_tuple(round(get<0>(pos) / grid_step),
                      round(get<1>(pos) / grid_step));
}
