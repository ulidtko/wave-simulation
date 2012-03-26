#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <memory>

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

private:
    GLuint texName;

    std::shared_ptr<Grid> grid;
};

#endif // MYGLWIDGET_H
