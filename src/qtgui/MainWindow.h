#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <memory>

#include "GridData.h"
#include "Simulation.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Grid> grid;
    std::shared_ptr<Simulation> simulation;

    QTimer timer;

private slots:
    void onTimer();
};

#endif // MAINWINDOW_H
