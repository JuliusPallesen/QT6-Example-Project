#include "AlarmsListModel.hpp"
#include "alarm.hpp"
#include <QQmlEngine>
#include <QtQuick>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<AlarmsListModel>("Alarm", 0, 1, "AlarmsModel");
  
    qRegisterMetaType<Alarm *>("AlarmObject");

    const QUrl url(QStringLiteral("qrc:/QtExampleProject/alarm.qml"));
    engine.load(url);

    return app.exec();
}
