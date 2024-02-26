#include "my_widget.hpp"
#include <QApplication>
#include <QPushButton>

/*
Implementation of final example for https://wiki.qt.io/Qt_for_Beginners

- Implementing:
    - derived QWidget class
        - using moc
        - implementing own signals
    - connections between application and buttons
    - button positioning and size changes
*/

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MyWidget my_widget(640, 480);

    QObject::connect(&my_widget, SIGNAL(requestQuit()), &app, SLOT(quit()));
    QObject::connect(&my_widget, SIGNAL(displayInfo()), &app, SLOT(aboutQt()));

    return app.exec();
}