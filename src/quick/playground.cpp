#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Hello World!\n";
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("cppText", "Hello World!");

    const QUrl url(QStringLiteral("QtExampleProject/helloworld.qml"));

    engine.load(url);

    return app.exec();
}
