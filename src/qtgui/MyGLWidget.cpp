#include "MyGLWidget.h"

#include <GL/gl.h>

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
