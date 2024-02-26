#pragma once
#include <string>

class Entity
{
  public:
    using Position = std::pair<uint32_t, uint32_t>;
    virtual Position getPosition();
    uint32_t getID() const;
    virtual ~Entity() = default;
    Entity(const Entity &) = delete;
    virtual std::string to_string() const;

  protected:
    Entity(const std::string &, const Position &);
    Entity(const Position &);
    const uint32_t m_id;
    const std::string m_name;
    Position m_position;

  private:
    static uint32_t ids;
};