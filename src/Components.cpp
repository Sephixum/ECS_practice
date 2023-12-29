#include "Components.hpp"

CTransform::CTransform(const Util::Vec2f &in_pos,
                       const Util::Vec2f &in_velocity, float in_angle) noexcept
    : pos(in_pos), velocity(in_velocity), angle(in_angle) {}

CShape::CShape(float in_radius, int in_sides, const sf::Color &in_color,
               const sf::Color &in_outlineColor, float in_thickness) noexcept
    : shape(in_radius, in_sides) {
  shape.setFillColor(in_color);
  shape.setOutlineColor(in_outlineColor);
  shape.setOutlineThickness(in_thickness);
  shape.setOrigin(in_radius, in_radius);
}

CCollision::CCollision(float in_radius) noexcept : radius(in_radius) {}

CScore::CScore(int in_score) noexcept : score(in_score) {}

CLifeSpan::CLifeSpan(int in_total) noexcept
    : remaining(in_total), total(in_total) {}

CInput::CInput() noexcept {}