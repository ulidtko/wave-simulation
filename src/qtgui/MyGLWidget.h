#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <memory>

#include "Perturbator.h"

class Grid;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0)
      : QGLWidget(parent)
    {}

    void setGrid(std::shared_ptr<Grid> arg) { grid = arg; }

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
public:
    auto getInteractivityFilter() -> Perturbator& { return perturber; }

private:
    GLuint texName;

    std::shared_ptr<Grid> grid;
    Perturbator perturber;
};

#endif // MYGLWIDGET_H
