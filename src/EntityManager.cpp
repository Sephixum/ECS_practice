#include "EntityManager.hpp"

#include <memory>

namespace Engine {

EntityManager::EntityManager() {}

auto EntityManager::addEntity(const std::string &tag) noexcept
    -> std::shared_ptr<Entity> {
  // create a new entity object
  // store it in the vector of all entities
  // store it in the map of tag->entityVectore
  // return the shared pointer pointing to that entity

  auto e = std::make_shared<Entity>(tag, ++m_totalEntities);
}

void EntityManager::update() {
  // called at begining of each frame by game engine
  // entities added will now be available to use this frame

  for (auto e : m_toAdd) {
    m_entities.push_back(e);
    m_entityMap[e->getTag()].push_back(e);
  }

  for (auto e : m_entities) {
    // if e is dead, remove it from m_entities
    // if e is dead, remove it from m_entitiyMap[e->getTag()]
    // hint: use std:remove_if
  }

  m_toAdd.clear();
}

} // namespace Engine
