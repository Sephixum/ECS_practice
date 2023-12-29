#pragma once

#include "Components.hpp"

#include <memory>
#include <string>
#include <type_traits>
#include <vector>

namespace Engine {

class Entity {
private:
  const size_t m_id = 0;
  const std::string m_tag = "Default";
  bool m_alive = true;

  Entity(const std::string &tag_in, size_t id_in);

  friend class EntityManager;

public:
  std::shared_ptr<CTransform> cTransform;
  std::shared_ptr<CShape> cShape;
  std::shared_ptr<CCollision> cCollision;
  std::shared_ptr<CInput> cInput;
  std::shared_ptr<CScore> cScore;
  std::shared_ptr<CLifeSpan> cLifeSpan;

  auto isActive() const noexcept -> bool;
  auto getTag() const noexcept -> const std::string &;
  auto getId() const noexcept -> const size_t;
  void destroy();
};

} // namespace Engine