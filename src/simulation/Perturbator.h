#ifndef PERTURBATOR_H
#define PERTURBATOR_H

#include <deque>
#include <boost/variant.hpp>

#include "GridData.h"

namespace Gesture {

struct RadialPulse {
    int i0, j0;
    float radius;
    float intensity;
};

struct MotionDrag {
    int i0, j0;
    float di, dj;
    float brushradius;
    float intensity;
};

struct LocalShear {
    // TODO
};
} // namespace Gesture

typedef
    boost::variant<
        Gesture::RadialPulse,
        Gesture::MotionDrag
    >
    AGesture;


class Perturbator
{
public:
    void operator() (Grid::data_type& d) { this->apply(d); }
    void apply(Grid::data_type&);

    Perturbator& enqueue(const AGesture& g) { this->queue.push_back(g); return *this; }

private:
    std::deque<AGesture> queue;
};

#endif // PERTURBATOR_H
