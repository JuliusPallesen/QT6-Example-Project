#pragma once

#include "alarm.hpp"
#include <QAbstractListModel>
#include <QObject>

class AlarmsListModel : public QAbstractListModel
{
    Q_OBJECT
  public:
    enum Roles { NameRole = Qt::UserRole, HoursRole, MinutesRole, OnRole, RepeatingRole };

    AlarmsListModel(QObject *parent = nullptr, bool fillWithDummyData = true)
      : QAbstractListModel(parent)
    {
        if (fillWithDummyData) {
            m_alarms.append(new Alarm("Morgenstund hat Gold im Mund", 6, 30, this));
            m_alarms.append(new Alarm("Schlumm-Schlumm", 10, 45, this));
            m_alarms.append(new Alarm("Wochenende", 9, 0, this));
        }
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return m_alarms.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid() || index.row() >= rowCount() || index.row() < 0) {
            return {};
        }
        const Alarm *alarm = m_alarms.at(index.row());
        switch (role) {
        case NameRole:
            return alarm->name();
        case HoursRole:
            return alarm->hours();
        case MinutesRole:
            return alarm->minutes();
        case OnRole:
            return alarm->on();
        case RepeatingRole:
            return alarm->repeating();
        default:
            return {};
        }
    }

    QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> roles = { { NameRole, "name" },
            { HoursRole, "hours" },
            { MinutesRole, "minutes" },
            { OnRole, "on" },
            { RepeatingRole, "repeating" } };
        return roles;
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        if (!index.isValid() || index.row() < 0 || index.row() >= rowCount()
            || role < Qt::UserRole) {
            return false;
        }

        Alarm *alarm = m_alarms.at(index.row());
        switch (role) {
        case NameRole:
            alarm->setName(value.toString());
            break;
        case HoursRole:
            alarm->setHours(value.toInt());
            break;
        case MinutesRole:
            alarm->setMinutes(value.toInt());
            break;
        case OnRole:
            alarm->setOn(value.toBool());
            break;
        case RepeatingRole:
            alarm->setRepeating(value.toBool());
            break;
        default:
            return false;
        }

        emit dataChanged(index, index, { role });
        return true;
    }

  private:
    QList<Alarm *> m_alarms;
};