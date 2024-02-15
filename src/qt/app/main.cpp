
#include <functional>
#include <iostream>
#include <string>

#include "mainwindow.h"
#include <QApplication>


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow mainW;
    mainW.show();
    mainW.setWindowTitle("Todo Application");

    return app.exec();
}
