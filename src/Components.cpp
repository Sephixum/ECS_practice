#include "Components.hpp"

namespace cmp {

Transform::Transform(const utl::Vec2f &in_pos, const utl::Vec2f &in_velocity,
                     float in_angle) noexcept
    : pos(in_pos), velocity(in_velocity), angle(in_angle) {}

Shape::Shape(float in_radius, int in_points, const sf::Color &in_color,
             const sf::Color &in_outlineColor,
             float in_outlineThickness) noexcept {
  shape.setRadius(in_radius);
  shape.setPointCount(in_points);
  shape.setFillColor(in_color);
  shape.setOutlineColor(in_outlineColor);
  shape.setOutlineThickness(in_outlineThickness);
  shape.setOrigin(in_radius, in_radius);
}

Collision::Collision(float in_radius) noexcept : radius(in_radius) {}

Score::Score(int in_score) noexcept : score(in_score) {}

LifeSpan::LifeSpan(int in_total) noexcept
    : remaining(in_total), total(in_total) {}

Input::Input() noexcept {}

} // namespace cmp
