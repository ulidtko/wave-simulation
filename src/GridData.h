#ifndef GRIDDATA_H
#define GRIDDATA_H

#include <boost/multi_array.hpp>

struct GridData
{
    typedef boost::multi_array<double, 3> data_type; // dimensions: x, y, displacement vector component (0 or 1)
    data_type data;

    GridData(float width, float height, float grid_step);
    void fill(double value);
};

#endif // GRIDDATA_H
