#include "ship.h"

Ship::Ship(const std::string &name) : Entity(name, { 0, 0 }) {}

Ship::Ship(const std::string &name, const Position &pos) : Entity(name, pos) {}

void Ship::setTarget(const Position &target)
{
    m_target = std::optional<Position>(target);
}

void Ship::setKnots(uint32_t knots) { m_knots = knots; }

std::string Ship::getName() const { return m_name; }

std::string Ship::to_string() const { return "I am a ship and my name is " + getName(); }
