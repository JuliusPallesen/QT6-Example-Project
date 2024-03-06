#pragma once

#include "alarm.hpp"
#include <QAbstractListModel>
#include <QCoreApplication>
#include <QDebug>
#include <QObject>

class AlarmsListModel : public QAbstractListModel
{
    Q_OBJECT
  public slots:
    void updateAlarms(int dayminutes)
    {
        for (size_t i = 0; i < m_alarms.size(); ++i) {
            const auto alarm = m_alarms[i];
            if (alarm->on() && alarm->minutes() + 60 * alarm->hours() == dayminutes) {
                const auto index = createIndex(i, 0);
                setData(index, true, TriggeredRole);
                emit triggeredAlarm(i);
                if (!alarm->repeating()) { setData(index, false, OnRole); }
            }
        }
    }
  signals:
    void triggeredAlarm(int);

  public:
    enum Roles {
        NameRole = Qt::UserRole,
        HoursRole,
        MinutesRole,
        OnRole,
        RepeatingRole,
        TriggeredRole
    };

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
        case TriggeredRole:
            return alarm->triggered();
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
            { RepeatingRole, "repeating" },
            { TriggeredRole, "triggered" } };
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
        case TriggeredRole:
            alarm->setTriggered(value.toBool());
            break;
        default:
            return false;
        }

        emit dataChanged(index, index, { role });
        return true;
    }

    bool insertRows(int row,
      int count = 1,
      const QModelIndex &parent = QModelIndex()) override
    {
        if (row < 0 || row > rowCount() || count < 0) { return false; }
        beginInsertRows(parent, row, row + count - 1);
        std::generate_n(std::back_inserter(m_alarms), count, [this]() {
            return new Alarm("added", 9, 0, this);
        });
        endInsertRows();
        return true;
    }

    bool removeRows(int row,
      int count = 1,
      const QModelIndex &parent = QModelIndex()) override
    {
        Q_UNUSED(parent);
        if (row < 0 || (row + count) >= m_alarms.size()) return false;
        beginRemoveRows(QModelIndex(), row, row + count - 1);
        for (int i = 0; i < count; ++i) { delete m_alarms.takeAt(row); }
        endRemoveRows();
        return true;
    }

    Q_INVOKABLE QVariantMap get(int row)
    {
        const QHash<int, QByteArray> roleNames = this->roleNames();
        const QModelIndex index = this->index(row, 0);
        QVariantMap result;

        for (const int roleId : roleNames.keys()) {
            result[roleNames[roleId]] = index.data(roleId);
        }

        return result;
    }

  private:
    QList<Alarm *> m_alarms;
};