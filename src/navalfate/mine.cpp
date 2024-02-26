#include "mine.h"
#include <random>

const uint32_t DriftingMine::MAXDRIFT = 1;

Mine::Mine(const Position &pos) : Entity(pos), damage(rand() % 10) {}

DriftingMine::DriftingMine(const Position &pos) : Mine(pos) {}
DriftingMine::DriftingMine() : Mine({ 0, 0 }) {}

Entity::Position DriftingMine::getPosition()
{
    drift();
    return Position();
}

void DriftingMine::drift()
{
    const uint32_t drift_x = (rand() % MAXDRIFT) - (rand() % MAXDRIFT);
    const uint32_t drift_y = (rand() % MAXDRIFT) - (rand() % MAXDRIFT);
    m_position = { m_position.first + drift_x, m_position.second + drift_y };
}

MooredMine::MooredMine(const Position &pos) : Mine(pos) {}

MooredMine::~MooredMine() {}