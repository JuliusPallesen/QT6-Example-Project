#include "AlarmsListModel.hpp"
#include "TimerBackend.hpp"
#include "alarm.hpp"
#include <QDateTime>
#include <QQmlEngine>
#include <QtQuick>

/*
Adds an alarm for debugging Purposes that instantly triggers
*/
void addDebugAlarm(AlarmsListModel *model)
{
    const auto currtime = QDateTime::currentDateTime().time();
    const auto currh = currtime.hour();
    const auto currm = currtime.minute() + 1;
    model->insertRows(model->rowCount(), 1);
    model->setData(
      model->index(model->rowCount() - 1, 0), currh, AlarmsListModel::HoursRole);
    model->setData(
      model->index(model->rowCount() - 1, 0), currm, AlarmsListModel::MinutesRole);
    model->setData(model->index(model->rowCount() - 1, 0), true, AlarmsListModel::OnRole);
    model->setData(model->index(model->rowCount() - 1, 0), "Debug", AlarmsListModel::NameRole);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TimerBackend *timerbackend = new TimerBackend(&app);
    engine.rootContext()->setContextProperty("timerbackend", timerbackend);

    AlarmsListModel *alarmModel = new AlarmsListModel(&app, true);
    engine.rootContext()->setContextProperty("alarmModel", alarmModel);
    addDebugAlarm(alarmModel);

    QObject::connect(
      timerbackend, SIGNAL(dayMinutesChanged(int)), alarmModel, SLOT(updateAlarms(int)));

    const QUrl url(QStringLiteral("qrc:/QtExampleProject/alarm.qml"));
    engine.load(url);

    return app.exec();
}
