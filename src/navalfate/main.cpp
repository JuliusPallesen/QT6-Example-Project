#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick>
#include <iostream>

int main(int argc, char *argv[])
{
    constexpr uint16_t GRID_SIZE = 16;

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("g_gridsize", GRID_SIZE);

    const QUrl url(QStringLiteral("qrc:/QtExampleProject/main.qml"));

    engine.load(url);

    return app.exec();
    return 0;
}
