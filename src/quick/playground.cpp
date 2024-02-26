#include "invokable.hpp"
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

    qmlRegisterType<Invokable>("backend.invokable", 0, 1, "Invokable");

    const QUrl url(QStringLiteral("QtExampleProject/helloworld.qml"));

    engine.load(url);

    return app.exec();
}
