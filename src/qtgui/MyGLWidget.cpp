#include "MyGLWidget.h"

#include <GL/gl.h>

#include "GridData.h"
#include "rendering/MeshRenderer.h"

void MyGLWidget::initializeGL() {
    glClearColor(0.2, 0.2, 0.2, 0.0);
}

void MyGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int m = std::min(w, h);
    glOrtho(-0.8*w/m, +10.0*w/m, -0.8*h/m, +10.0*h/m, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    MeshRenderer::render(*grid);
}
