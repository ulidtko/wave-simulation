#include "ImageRenderer.h"

#include <GL/glu.h>

#include <tuple>

using std::tuple;
using std::tie;

template<typename Float>
void inline glVertex2(Float x, Float y);
template<> void glVertex2<double>(double x, double y) { glVertex2d(x, y); }
template<> void glVertex2<float>(float x, float y) { glVertex2f(x, y); }

template<typename Float>
void inline glVertex(const tuple<Float, Float>& p2) {
    Float x, y;
    tie(x, y) = p2;
    glVertex2(x, y);
}

template<typename T>
void inline glTexCoord2(T x, T y);
template<> void glTexCoord2<double>(double x, double y) { glTexCoord2d(x, y); }
template<> void glTexCoord2<float>(float x, float y) { glTexCoord2f(x, y); }

template<typename T>
void inline glTexCoord(const tuple<T, T>& p2) {
    T x, y;
    tie(x, y) = p2;
    glTexCoord2(x, y);
}


void ImageRenderer::render(const Grid &grid) {
    std::array<size_t, 3> grid_shape;
    std::copy_n(grid.data.shape(), 3, grid_shape.begin());

    for(size_t i = 1; i < grid_shape[0]; ++i) {
        glBegin(GL_QUAD_STRIP);
        for(size_t j = 1; j < grid_shape[1]; ++j) {
            glTexCoord(grid.getNodeOrigin(i-1, j-1)); glVertex(grid.getNodePosition(i-1, j-1));
            glTexCoord(grid.getNodeOrigin(i,   j-1)); glVertex(grid.getNodePosition(i,   j-1));
            glTexCoord(grid.getNodeOrigin(i-1, j));   glVertex(grid.getNodePosition(i-1, j));
            glTexCoord(grid.getNodeOrigin(i,   j));   glVertex(grid.getNodePosition(i, j));
        }
        glEnd();
    }
}
