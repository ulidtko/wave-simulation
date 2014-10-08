#include "GridData.h"

#include <cmath>

using std::make_tuple;
using std::get;

Grid::Grid(float width, float height, float grid_step)
    : width(width)
    , height(height)
    , grid_step(grid_step)
    , shape(this->initShape())
    , data(shape)
{}

decltype(Grid::shape)
Grid::initShape()
{
    uint width_cells = width / grid_step;
    uint height_cells = height / grid_step;

    return {width_cells, height_cells, 2};
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
