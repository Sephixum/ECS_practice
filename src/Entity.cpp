#include "Entity.hpp"

namespace eng {

Entity::Entity(const std::string &in_tag, size_t in_id)
    : m_id(in_id), m_tag(in_tag) {}

auto Entity::isAlive() const noexcept -> bool { return m_alive; }

auto Entity::getTag() const noexcept -> const std::string & { return m_tag; }

void Entity::destroy() noexcept { m_alive = false; }

} // namespace eng
