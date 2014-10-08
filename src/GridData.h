#ifndef GRIDDATA_H
#define GRIDDATA_H

#include <boost/multi_array.hpp>
#include <tuple>
#include <array>

using std::tuple;

class Grid
{
public:
    const float width;
    const float height;
    const float grid_step;
    const std::array<size_t, 3> shape;

    typedef boost::multi_array<double, 3> data_type;
    data_type data;

    Grid(float width, float height, float grid_step);

    void fill(double value);

    tuple<double,double> getNodeOrigin(int i, int j) const;
    tuple<double,double> getNodePosition(int i, int j) const;
    tuple<int,int> getNearestNode(tuple <double,double> pos) const;

private:
    auto initShape() -> decltype(shape);
};


#endif // GRIDDATA_H
