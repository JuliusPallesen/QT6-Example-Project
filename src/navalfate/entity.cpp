#include "entity.h"

Entity::Entity(const std::string &name, const Position &pos)
  : m_name(name), m_id(++ids), m_position(pos)
{}

Entity::Entity(const Position &pos) : m_position(pos), m_id(++ids) {}

Entity::Position Entity::getPosition() { return m_position; }

uint32_t Entity::getID() const { return m_id; }

std::string Entity::to_string() const { return "I am an Entity."; }

uint32_t Entity::ids = 0;
