#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <memory>

#include "simulation/GridData.h"
#include "simulation/Simulation.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private:
    std::shared_ptr<Ui::MainWindow> ui;

    std::shared_ptr<Grid> grid;
    std::shared_ptr<Simulation> simulation;

    QTimer timer;

private slots:
    void onTimer();
};

#endif // MAINWINDOW_H
