#pragma once

#include "entity.h"

class Mine : public Entity
{
  public:
  protected:
    Mine(const Position &);

  private:
    uint32_t damage;
};

class MooredMine : public Mine
{
  public:
    MooredMine(const Position &);
    ~MooredMine();

  private:
};

class DriftingMine : public Mine
{
  public:
    DriftingMine(const Position &);
    DriftingMine();
    virtual Position getPosition();

  private:
    const static uint32_t MAXDRIFT;
    void drift();
};
