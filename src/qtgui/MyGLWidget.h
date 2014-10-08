#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <memory>

class Grid;
class Simulation;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0)
      : QGLWidget(parent)
    {}

    void setGrid(std::shared_ptr<Grid> arg) { grid = arg; }
    void setSimulation(std::shared_ptr<Simulation> arg) { simulation = arg; }

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

private:
    GLuint texName;

    std::shared_ptr<Grid> grid;
    std::shared_ptr<Simulation> simulation;
};

#endif // MYGLWIDGET_H
