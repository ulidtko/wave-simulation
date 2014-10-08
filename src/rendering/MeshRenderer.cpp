#include "MeshRenderer.h"

#include <array>
#include <GL/gl.h>

#include "simulation/GridData.h"

using std::tie;

void MeshRenderer::render(const Grid& grid) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(255, 255, 255);

    std::array<size_t, 3> grid_shape;
    std::copy_n(grid.data.shape(), 3, grid_shape.begin());

    for(size_t i = 0; i < grid_shape[0]; ++i) {
        glBegin(GL_LINE_STRIP);
        for(size_t j = 0; j < grid_shape[1]; ++j) {
            double x, y;
            tie(x, y) = grid.getNodePosition(i, j);
            glVertex2d(x, y);
        }
        glEnd();
    }

    for(size_t j = 0; j < grid_shape[1]; ++j) {
        glBegin(GL_LINE_STRIP);
        for(size_t i = 0; i < grid_shape[0]; ++i) {
            double x, y;
            tie(x, y) = grid.getNodePosition(i, j);
            glVertex2d(x, y);
        }
        glEnd();
    }
}
