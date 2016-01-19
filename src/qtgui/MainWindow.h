#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTimer>
#include <memory>

#ifndef Q_MOC_RUN // workaround for QTBUG-22829

#include "simulation/GridData.h"
#include "simulation/Simulation.h"

#endif // Q_MOC_RUN

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
