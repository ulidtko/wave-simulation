#include "Perturbator.h"

#include <tuple>
#include <vector>

using std::tuple;
using std::tie;
using std::vector;

struct gesture_visitor : boost::static_visitor<void> {
    explicit gesture_visitor(Grid::data_type& grid)
        : grid(grid)
    {}
    Grid::data_type& grid;

    void operator() (const Gesture::RadialPulse& pulse) const {
        vector<tuple<int,int>> circlePoints;
        auto addPoint = [&](int x, int y) { circlePoints.emplace_back(x, y); };

        // the Midpoint circle algorithm
        int x = pulse.radius;
        int y = 0;
        int radiusError = 1 - x;
        while (x >= y) {
            addPoint( x,  y);
            addPoint(-x,  y);
            addPoint( x, -y);
            addPoint(-x, -y);
            addPoint( y,  x);
            addPoint(-y,  x);
            addPoint( y, -x);
            addPoint(-y, -x);

            ++y;
            if (radiusError < 0)
                radiusError += 2 * y + 1;
            else {
                --x;
                radiusError += 2 * (y - x + 1);
            }
        }

        for (auto& p: circlePoints) {
            int cx, cy;
            tie(cx, cy) = p;

            uint j = cx + pulse.j0;
            uint i = cy + pulse.i0;
            if (i > 0 && i < grid.shape()[0] &&
                j > 0 && j < grid.shape()[1])
            {
                grid[i][j][0] += cy / pulse.radius * pulse.intensity;
                grid[i][j][1] += cx / pulse.radius * pulse.intensity;
            }
        }
    }

    void operator() (const Gesture::MotionDrag& drag) const {
        // TODO
    }
};

void Perturbator::apply(Grid::data_type& grid) {
    for (auto& gesture: queue) {
        boost::apply_visitor(gesture_visitor(grid), gesture);
    }
    queue.clear();
}
