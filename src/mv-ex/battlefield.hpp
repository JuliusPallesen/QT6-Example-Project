#include "tiles.h"
#include <QAbstractTableModel>
#include <QObject>
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Battlefield : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
  public:
    Battlefield(uint32_t rows = 8, uint32_t cols = 8, QObject *parent = nullptr)
      : m_rows(rows), m_cols(cols), m_field(initField(rows, cols)),
        QAbstractTableModel(parent)
    {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return m_rows;
    };
    int columnCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return m_cols;
    };

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (index.isValid() && index.column() < m_cols && index.row() < m_rows) {
            return QVariant::fromValue(m_field[index.row()][index.column()]);
        }
        return QModelIndex();
    }

    QModelIndex
      index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
    {
        if (row < m_rows && column < m_cols) {
            return QAbstractItemModel::createIndex(row, column);
        }
        return QModelIndex();
    }

    bool setData(const QModelIndex &index,
      const QVariant &value,
      int role = Qt::EditRole) override
    {
        if (index.isValid() && index.column() < m_cols && index.row() < m_rows) {
            if (auto *tilePtr = qvariant_cast<Tile *>(value)) {
                m_field[index.row()][index.column()] = tilePtr;
                return true;
            }
        }
        return false;
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override
    {
        if (index.isValid()) {
            if (index.isValid() && index.column() < m_cols && index.row() < m_rows) {
                return m_field[index.row()][index.column()]->getFlags();
            }
        }
        return {};
    }

  private:
    using field = std::vector<std::vector<Tile *>>;
    field m_field;
    const uint32_t m_rows;
    const uint32_t m_cols;

    field initField(uint32_t rows, uint32_t cols)
    {
        field f = field(rows, std::vector<Tile *>(cols, new Tile(this)));
        return f;
    }
};