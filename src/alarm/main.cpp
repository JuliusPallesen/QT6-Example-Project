#include "AlarmsListModel.hpp"
#include "TimerBackend.hpp"
#include "alarm.hpp"
#include <QQmlEngine>
#include <QtQuick>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TimerBackend *timer = new TimerBackend(&app);
    engine.rootContext()->setContextProperty("timer", timer);

    AlarmsListModel *alarmModel = new AlarmsListModel(&app, true);
    engine.rootContext()->setContextProperty("alarmModel", alarmModel);

    QObject::connect(
      timer, SIGNAL(currentTimeChanged(int)), alarmModel, SLOT(updateAlarms(int)));

    qmlRegisterType<AlarmsListModel>("Alarm", 0, 1, "AlarmsModel");
    qmlRegisterType<TimerBackend>("Alarm", 0, 1, "TimerBackend");

    qRegisterMetaType<Alarm *>("AlarmObject");

    const QUrl url(QStringLiteral("qrc:/QtExampleProject/alarm.qml"));
    engine.load(url);


    return app.exec();
}
