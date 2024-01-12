#include "EntityManager.hpp"
#include <algorithm>

namespace eng {

EntityManager::EntityManager() {}

void EntityManager::update() {
  for (auto entity : m_entitiesToAdd) {
    m_entities.push_back(entity);
    m_entityMap[entity->getTag()].push_back(entity);
  }

  m_entitiesToAdd.clear();

  m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
                                  [](const auto &entity) -> bool {
                                    return !entity->isAlive();
                                  }),
                   m_entities.end());
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

} // namespace eng
