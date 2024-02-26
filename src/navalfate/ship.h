#pragma once

#include "entity.h"
#include <optional>
#include <string>

class Ship : public Entity
{
  public:
    Ship(const std::string &);
    Ship(const std::string &, const Position &);
    void setTarget(const Position &);
    void setKnots(uint32_t);
    std::string getName() const;
    std::string to_string() const override;

  protected:
    std::optional<Position> m_target;
    uint32_t m_knots;
    uint32_t health;
};