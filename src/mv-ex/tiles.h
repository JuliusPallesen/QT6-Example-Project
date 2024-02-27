#include <QObject>
#include <QQmlEngine>

class Tile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(TileType tile_type READ tile_type NOTIFY typeChanged)
  public:
    enum TileType { Water, Ship, Mine };
    Q_ENUMS(TileType)

    Tile(QObject *parent = nullptr, TileType type = TileType::Water)
      : m_type(type), QObject(parent)
    {}
    ~Tile() = default;
    TileType tile_type() { return m_type; }

    static void declareQML() { qmlRegisterType<Tile>("Tile", 0, 1, "Tile"); }

  private:
    QString m_img_url;
    TileType m_type;

  signals:
    void typeChanged();
};

class ShipTile : public Tile
{
    Q_OBJECT
  public:
    ShipTile(QObject *parent = nullptr) : Tile(parent, TileType::Ship) {}
};

class MineTile : public Tile
{
    Q_OBJECT
  public:
    MineTile(QObject *parent = nullptr) : Tile(parent, TileType::Mine) {}
};
