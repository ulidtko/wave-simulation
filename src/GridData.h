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

    typedef boost::multi_array<double, 3> data_type;
    data_type data;

    Grid(float width, float height, float grid_step);

    void fill(double value);

    tuple<double,double> getNodeOrigin(int i, int j) const;
    tuple<double,double> getNodePosition(int i, int j) const;

private:
    std::array<size_t, 3> shape;

    int getEquationNumber(int i, int j) { return i + j * shape[0]; }
    tuple<int,int> getEquationNode(int k) { return std::make_tuple(k % shape[0], k / shape[0]); }

    friend class Simulation; // yeah, i suck at OO design :(
};

#endif // GRIDDATA_H
