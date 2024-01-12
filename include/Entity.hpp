#pragma once

#include "Components.hpp"

#include <memory>

namespace eng {

class Entity {

  friend class EntityManager;

private:
  const size_t m_id = 0;
  const std::string m_tag = "Default";
  bool m_alive = true;

  Entity(const std::string &tag_in, size_t id_in);

public:
  std::shared_ptr<cmp::Transform> cTransform;
  std::shared_ptr<cmp::Shape> cShape;
  std::shared_ptr<cmp::Collision> cCollision;
  std::shared_ptr<cmp::Input> cInput;
  std::shared_ptr<cmp::Score> cScore;
  std::shared_ptr<cmp::LifeSpan> cLifeSpan;

  auto isAlive() const noexcept -> bool;
  auto getTag() const noexcept -> const std::string &;
  void destroy() noexcept;
};

} // namespace eng
