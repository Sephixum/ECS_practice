#include "EntityManager.hpp"

#include <algorithm>

namespace eng {

void EntityManager::_remove_dead_entities() {
  m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(),
                                  [](const auto &entity) -> bool {
                                    return !entity->isAlive();
                                  }),
                   m_entities.end());

  for (auto &map : m_entityMap) {
    auto &vec = map.second;
    vec.erase(std::remove_if(vec.begin(), vec.end(),
                             [](const auto &entity) -> bool {
                               return !entity->isAlive();
                             }),
              vec.end());
  }
}

EntityManager::EntityManager() {}

void EntityManager::update() {
  for (auto entity : m_entitiesToAdd) {
    m_entities.push_back(entity);
    m_entityMap[entity->getTag()].push_back(entity);
  }
  m_entitiesToAdd.clear();

  _remove_dead_entities();
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
