#pragma once

#include "entity.h"
#include "ship.h"
#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <type_traits>
#include <unordered_map>

template<class T>
concept DerivedFromEntity = std::is_base_of<Entity, T>::value;

template<uint32_t N> class Battlefield
{
  public:
    using EntityPointer = std::shared_ptr<Entity>;
    using ShipPointer = std::shared_ptr<Ship>;
    using ShipMap = std::unordered_map<std::string, ShipPointer>;
    using IdMap = std::map<uint32_t, EntityPointer>;
    using Field2D = std::array<std::array<EntityPointer, N>, N>;

    ShipPointer getByName(const std::string &);

    EntityPointer getAt(const Entity::Position &);

    EntityPointer getByID(const uint32_t &);

    template<class T, class... Args>
        requires DerivedFromEntity<T>
    std::shared_ptr<T> emplace(Args &&...);

  private:
    ShipMap m_entities;
    Field2D m_field;
    IdMap m_ids;

    bool isInBounds(const Entity::Position &);
};

template<uint32_t N>
Battlefield<N>::ShipPointer Battlefield<N>::getByName(const std::string &name)
{
    if (m_entities.count(name) > 0) { return static_cast<ShipPointer>(m_entities[name]); }
    return {};
}

template<uint32_t N>
Battlefield<N>::EntityPointer Battlefield<N>::getAt(const Entity::Position &pos)
{
    if (isInBounds(pos)) { return m_field[pos.second][pos.first]; }
    return {};
}

template<uint32_t N>
Battlefield<N>::EntityPointer Battlefield<N>::getByID(const uint32_t &id)
{
    if (m_ids.count(id) > 0) { return m_ids[id]; }
    return {};
}

template<uint32_t N> bool Battlefield<N>::isInBounds(const Entity::Position &pos)
{
    return pos.first < N && pos.second < N;
}

template<uint32_t N> template<class T, class... Args>
    requires DerivedFromEntity<T>
std::shared_ptr<T> Battlefield<N>::emplace(Args &&...args)
{
    const auto ptr = std::make_shared<T>(
      std::forward<Args>(args)...); // T of Args may be &Type, so we may forward it
    const auto p = ptr->getPosition();
    m_field[p.second][p.first] = ptr;
    m_ids[ptr->getID()] = ptr;
    if (std::is_base_of<Ship, T>::value) { m_entities[ptr->getName()] = ptr; }
    return ptr;
}
