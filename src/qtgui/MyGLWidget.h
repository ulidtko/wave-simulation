#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0)
      : QGLWidget(parent) {}

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

};

#endif // MYGLWIDGET_H
