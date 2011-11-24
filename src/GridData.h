#ifndef GRIDDATA_H
#define GRIDDATA_H

#include <boost/multi_array.hpp>
#include <tuple>

using std::tuple;

class GridData
{
public:
    typedef boost::multi_array<double, 3> data_type; // dimensions: x, y, displacement vector component (0 or 1)
    data_type data;

    GridData(float width, float height, float grid_step);
    void fill(double value);

    tuple<double,double> getNodeOrigin(int i, int j) const;
    tuple<double,double> getNodePosition(int i, int j) const;

private:
    float width;
    float height;
    float grid_step;
};

#endif // GRIDDATA_H
