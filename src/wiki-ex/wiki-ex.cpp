#include <QApplication>
#include <QPushButton>
#include "my_widget.hpp"

/*
Implementation of final example for https://wiki.qt.io/Qt_for_Beginners

- Implementing:
    - derived QWidget
    - connections between application and buttons
*/

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MyWidget my_widget(640, 480);

    QObject::connect(&my_widget, SIGNAL(requestQuit()), &app, SLOT(quit()));
    QObject::connect(&my_widget, SIGNAL(displayInfo()), &app, SLOT(aboutQt()));

    return app.exec();
}