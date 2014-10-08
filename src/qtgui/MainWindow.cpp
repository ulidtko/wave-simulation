#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>

const float kMaxTps = 20.0; // simulation ticks per second

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , grid(new Grid(12.0, 8.0, 0.2))
    , simulation(new Simulation(grid, 1.0 / kMaxTps, 3.0))
{
    ui->setupUi(this);
    ui->centralwidget->setGrid(grid);
    ui->centralwidget->setSimulation(simulation);

    simulation->reset();
    simulation->filters.emplace_back(std::ref(
        simulation->interactor.getInteractivityFilter()
    ));

    timer.setInterval(1000 / kMaxTps);
    this->connect(&timer, SIGNAL(timeout()), SLOT(onTimer()));
    timer.start();
}

void MainWindow::onTimer() {
    simulation->advanceOneTick();
    ui->centralwidget->repaint();
}
