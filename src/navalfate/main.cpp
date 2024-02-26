#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Naval Fate.\n";
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/QtExampleProject/main.qml"));

    engine.load(url);

    return app.exec();
    return 0;
}
