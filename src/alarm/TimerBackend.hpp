#pragma once

#include <QDateTime>
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
        m_qtimer->setInterval(60000);
        m_qtimer->setSingleShot(true);

        QObject::connect(m_qtimer, &QTimer::timeout, this, &TimerBackend::timerTimeout);

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
        setCurrentTime(currentTime.toString("h:m"));
        setDayMinutes(currentTime.time().minute() + 60 * currentTime.time().hour());
    }

  signals:
    void currentTimeChanged();
    void dayMinutesChanged(int);

  private:
    QTimer *m_qtimer;
    int m_dayminutes;
    QString m_currenttime;
};
