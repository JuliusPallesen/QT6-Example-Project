#pragma once

#include <QObject>

class Alarm : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(int hours READ hours WRITE setHours NOTIFY hoursChanged);
    Q_PROPERTY(int minutes READ minutes WRITE setMinutes NOTIFY minutesChanged);
    Q_PROPERTY(bool repeating READ repeating WRITE setRepeating NOTIFY repeatingChanged);
    Q_PROPERTY(bool on READ on WRITE setOn NOTIFY onChanged);
    Q_PROPERTY(bool triggered READ triggered WRITE setTriggered NOTIFY triggeredChanged);

  public:
    Alarm(QString name = "",
      uint8_t hours = 0,
      uint8_t minutes = 0,
      bool on = true,
      bool repeating = false,
      QObject *parent = nullptr)
      : QObject(parent), m_name(name), m_hours(hours), m_minutes(minutes), m_on(on), m_repeating(repeating)
    {}
    QString name() const { return m_name; }
    int hours() const { return m_hours; }
    int minutes() const { return m_minutes; }
    bool on() const { return m_on; }
    bool repeating() const { return m_repeating; }
    bool triggered() const { return m_triggered; }

public slots:
    void setName(QString name)
    {
        if (name == m_name) { return; }
        m_name = name;
        emit nameChanged();
    }
    void setHours(int hours)
    {
        if (hours == m_hours) { return; }
        m_hours = hours;
        emit hoursChanged();
    }
    void setMinutes(int minutes)
    {
        if (minutes == m_minutes) { return; }
        m_minutes = minutes;
        emit minutesChanged();
    }
    void setOn(bool on)
    {
        if (on == m_on) { return; }
        m_on = on;
        emit onChanged();
    }
    void setRepeating(bool repeating)
    {
        if (repeating == m_repeating) { return; }
        m_repeating = repeating;
        emit repeatingChanged();
    }

    void setTriggered(bool triggered)
    {
        if (triggered == m_triggered) { return; }
        m_triggered = triggered;
        emit triggeredChanged();
    }
    
  signals:
    void nameChanged();
    void hoursChanged();
    void minutesChanged();
    void repeatingChanged();
    void onChanged();
    void triggeredChanged();

  private:
    uint8_t m_hours;
    uint8_t m_minutes;
    bool m_repeating;
    bool m_on;
    bool m_triggered;
    QString m_name;
};
