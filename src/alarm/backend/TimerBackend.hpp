#pragma once

#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QTimer>

class TimerBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(
      QString currentTime READ currentTime WRITE setCurrentTime NOTIFY currentTimeChanged)
    Q_PROPERTY(
      int dayMinutes READ dayMinutes WRITE setDayMinutes NOTIFY dayMinutesChanged)
  public:
    TimerBackend(QObject *parent = nullptr) : QObject(parent)
    {
        m_qtimer = new QTimer(this);
        m_qtimer->setInterval(1000);
        m_qtimer->setSingleShot(false);

        connect(m_qtimer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
        m_qtimer->start();

        timerTimeout();
    }

    QString currentTime() { return m_currenttime; }
    int dayMinutes() { return m_dayminutes; }
  public slots:

    void setCurrentTime(QString currtime)
    {
        if (m_currenttime == currtime) { return; }
        m_currenttime = currtime;
        emit currentTimeChanged();
    }
    void setDayMinutes(int mins)
    {
        if (m_dayminutes = mins) { return; }
        m_dayminutes = mins;
        emit dayMinutesChanged(m_dayminutes);
    }

    void timerTimeout()
    {
        QDateTime currentTime = QDateTime::currentDateTime().toLocalTime();
        setCurrentTime(currentTime.toString("h:mm"));
        // only trigger minute update once every minute
        if (currentTime.time().minute() != __last_minute) {
            setDayMinutes(currentTime.time().minute() + 60 * currentTime.time().hour());
            __last_minute = currentTime.time().minute();
            emit dayMinutesChanged(m_dayminutes);
        }
    }

  signals:
    void currentTimeChanged();
    void dayMinutesChanged(int);

  private:
    int m_dayminutes;
    int __last_minute;
    QTimer *m_qtimer;
    QString m_currenttime;
};
