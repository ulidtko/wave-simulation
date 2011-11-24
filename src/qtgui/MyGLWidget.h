#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include <memory>

class GridData;

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0)
      : QGLWidget(parent) {}

    void setGrid(std::shared_ptr<GridData> arg) { grid = arg; }

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    std::shared_ptr<GridData> grid;
};

#endif // MYGLWIDGET_H
