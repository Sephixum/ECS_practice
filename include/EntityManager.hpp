#pragma once

#include "Entity.hpp"

#include <map>
#include <vector>

namespace eng {

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map<std::string, EntityVec>;

class EntityManager {
private:
  EntityVec m_entitiesToAdd;

  EntityVec m_entities;
  EntityMap m_entityMap;

  size_t m_totalEntities = 0;

  void _remove_dead_entities();

public:
  EntityManager();
  void update();
  auto addEntity(const std::string &tag) noexcept -> std::shared_ptr<Entity>;
  auto getEntities() noexcept -> const EntityVec &;
  auto getEntities(const std::string &tag) noexcept -> const EntityVec &;
};

} // namespace eng
