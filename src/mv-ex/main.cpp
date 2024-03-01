#include "tiles.h"
#include "battlefield.hpp"
#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringListModel>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Needed to use Type Enum in QML
    qmlRegisterType<Tile>("Tile", 0, 1, "Tile");

    QList<Tile *> Tile_list;

    constexpr uint32_t g_gridsize = 8;

    for (size_t i = 0; i < g_gridsize * g_gridsize; i++) {
        Tile *tile;
        switch (rand() % 3) {
        case 0:
            tile = new Tile;
            break;
        case 1:
            tile = new MineTile;
            break;
        case 2:
            tile = new ShipTile;
            break;
        default:
            break;
        }
        Tile_list.append(tile);
    }

    engine.rootContext()->setContextProperty("myObjects", QVariant::fromValue(Tile_list));
    qmlRegisterType<Battlefield>("Battlefield", 1, 0, "Battlefield");

    const QUrl url(QStringLiteral("qrc:/QtExampleProject/main.qml"));
    engine.load(url);

    return app.exec();
}
