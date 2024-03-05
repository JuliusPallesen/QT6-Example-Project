#include "AlarmsListModel.hpp"
#include "TimerBackend.hpp"
#include "alarm.hpp"
#include <QQmlEngine>
#include <QtQuick>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TimerBackend *timerbackend = new TimerBackend(&app);
    engine.rootContext()->setContextProperty("timerbackend", timerbackend);

    AlarmsListModel *alarmModel = new AlarmsListModel(&app, true);
    engine.rootContext()->setContextProperty("alarmModel", alarmModel);

    QObject::connect(
      timerbackend, SIGNAL(dayMinutesChanged(int)), alarmModel, SLOT(updateAlarms(int)));

    const QUrl url(QStringLiteral("qrc:/QtExampleProject/alarm.qml"));
    engine.load(url);

    return app.exec();
}
