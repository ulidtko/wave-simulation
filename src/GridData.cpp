#include "GridData.h"

GridData::GridData(float width, float height, float grid_step)
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
