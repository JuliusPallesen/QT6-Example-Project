#include <QGuiApplication>
#include <QtQuick>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Hello World!\n";
    QGuiApplication app(argc, argv);
    QQuickView view;

    view.setSource(QUrl("helloworld.qml"));
    view.show();

    return app.exec();
}
