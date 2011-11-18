#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("Wave Simulation");

    MainWindow w;
    w.show();

    return app.exec();
}
