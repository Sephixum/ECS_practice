#include "Entity.hpp"

namespace Engine {

Entity::Entity(const std::string &tag_in, size_t id_in)
    : m_id(id_in), m_tag(tag_in) {}

auto Entity::isActive() const noexcept -> bool { return m_alive; }

auto Entity::getTag() const noexcept -> const std::string & { return m_tag; }

auto Entity::getId() const noexcept -> const size_t { return m_id; }

void Entity::destroy() {}

} // namespace Engine
