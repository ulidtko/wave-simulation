#include "MyGLWidget.h"

#include <tuple>

#include <QMouseEvent>
#include <QDebug>
#include <GL/gl.h>
#include <GL/glu.h>

#include "GridData.h"
#include "rendering/MeshRenderer.h"
#include "rendering/ImageRenderer.h"

void MyGLWidget::initializeGL() {
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.2, 0.2, 0.2, 0.0);

    auto img = QImage(":/android.jpg");
    texName = bindTexture(img, GL_TEXTURE_2D, GL_RGB,
                          QGLContext::InvertedYBindOption | QGLContext::LinearFilteringBindOption);
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

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texName);

    ImageRenderer::render(*grid);
    //MeshRenderer::render(*grid);
}

tuple<float,float> window2scene(const QPoint& winCoord) {
    /* this function is © 1997-2014 NeHe Productions at Gamedev.net */
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);

    GLfloat winX = winCoord.x();
    GLfloat winY = viewport[3] - winCoord.y();
    GLfloat winZ;
    glReadPixels(winX, winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

    GLdouble resX, resY, resZ;
    gluUnProject(winX, winY, winZ,
                 modelview, projection, viewport,
                 &resX, &resY, &resZ);
    return std::make_tuple(resX, resY);
}

void MyGLWidget::mousePressEvent(QMouseEvent* e) {
    using std::get;
    auto gridpos = grid->getNearestNode(window2scene(e->pos()));
    auto pulse = Gesture::RadialPulse{get<0>(gridpos), get<1>(gridpos), 3.0, 0.4};
    perturber.enqueue(pulse);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent* e) {

}

void MyGLWidget::mouseReleaseEvent(QMouseEvent* e) {

}
