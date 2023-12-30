#include "EntityManager.hpp"

#include <memory>

namespace Engine {

EntityManager::EntityManager() {}

void EntityManager::update() {
  // called at begining of each frame by game engine
  // entities added will now be available to use this frame

  for (auto e : m_entitiesToAdd) {
    m_entities.push_back(e);
    m_entityMap[e->getTag()].push_back(e);
  }

  for (auto e : m_entities) {
    // if e is dead, remove it from m_entities
    // if e is dead, remove it from m_entitiyMap[e->getTag()]
    // hint: use std:remove_if
  }

  m_entitiesToAdd.clear();
}

auto EntityManager::addEntity(const std::string &tag) noexcept
    -> std::shared_ptr<Entity> {
  auto entity = std::shared_ptr<Entity>(new Entity(tag, ++m_totalEntities));
  m_entitiesToAdd.push_back(entity);

  return entity;
}

auto EntityManager::getEntities() noexcept -> const EntityVec & {
  return m_entities;
}

auto EntityManager::getEntities(const std::string &tag) noexcept
    -> const EntityVec & {
  return m_entityMap[tag];
}

// void EntityManager::removeDeadEntities(EntityVec &vec) { vec.clear(); }

} // namespace Engine
