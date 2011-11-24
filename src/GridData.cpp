#include "GridData.h"

using std::make_tuple;

GridData::GridData(float width, float height, float grid_step)
    : width(width)
    , height(height)
    , grid_step(grid_step)
{
    int width_cells = width / grid_step;
    int height_cells = height / grid_step;

    data_type::extent_gen extents;
    data.resize(extents[width_cells][height_cells][2]);
}


void GridData::fill(double value)
{
    for(auto d2 : data)
        for(auto d1 : d2)
            for(auto& el : d1)
            {
                el = value;
            }
}


tuple<double,double> GridData::getNodeOrigin(int i, int j) const {
    return make_tuple(i * grid_step, j * grid_step);
}


tuple<double,double> GridData::getNodePosition(int i, int j) const {
    return make_tuple(i * grid_step + data[i][j][0],
                      j * grid_step + data[i][j][1]);
}
