#include "MyGLWidget.h"

#include <GL/gl.h>

void MyGLWidget::initializeGL() {
    glClearColor(0.2, 0.2, 0.2, 0.0);
}

void MyGLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int m = std::min(w, h);
    glOrtho(-5.0*w/m, +5.0*w/m, -5.0*h/m, +5.0*h/m, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2d(0.0, 0.0);
    glVertex2d(1.0, 0.0);
    glVertex2d(0.0, 1.0);
    glEnd();
}
