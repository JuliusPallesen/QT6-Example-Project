#pragma once

#include <QObject>
#include <QtQml>

class Invokable : public QObject
{
    Q_OBJECT
    QML_ELEMENT
  public:
    explicit Invokable(QObject *parent = nullptr) { Q_UNUSED(parent); };
    Q_INVOKABLE int getVal() { return m_val; }
    Q_INVOKABLE void setVal(int val) { m_val = val; }
    Q_INVOKABLE int pow2() { return m_val * m_val; }

  private:
    int m_val;
};