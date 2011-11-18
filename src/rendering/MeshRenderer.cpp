#include "MeshRenderer.h"

#include <array>
#include <GL/gl.h>

#include "GridData.h"

void MeshRenderer::render(const GridData& grid) {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3ub(255, 255, 255);

    std::array<size_t, 3> grid_shape;
    std::copy_n(grid.data.shape(), 3, grid_shape.begin());

    for(size_t i = 0; i < grid_shape[0]; ++i) {
        glBegin(GL_LINE_STRIP);
        for(size_t j = 0; j < grid_shape[1]; ++j) {
            auto const& displacement = grid.data[i][j];
            std::array<double,2> position = {{1.0 * i, 1.0 * j}};
            glVertex2d(position[0] + displacement[0], position[1] + displacement[1]);
        }
        glEnd();
    }

    for(size_t j = 0; j < grid_shape[1]; ++j) {
        glBegin(GL_LINE_STRIP);
        for(size_t i = 0; i < grid_shape[0]; ++i) {
            auto const& displacement = grid.data[i][j];
            std::array<double,2> position = {{1.0 * i, 1.0 * j}};
            glVertex2d(position[0] + displacement[0], position[1] + displacement[1]);
        }
        glEnd();
    }
}
