#pragma once

#include "Vec2/Vec2.hpp"

#include <SFML/Graphics/CircleShape.hpp>

namespace cmp {

struct Transform {
  utl::Vec2f pos = {0.0f, 0.0f};
  utl::Vec2f velocity = {0.0f, 0.0f};
  float angle = 0.0f;

  Transform() = default;
  Transform(const utl::Vec2f &in_pos, const utl::Vec2f &in_velocity,
            float in_angle) noexcept;
};

struct Shape {
  sf::CircleShape shape;

  Shape(float in_radius, int in_points,
        const sf::Color &in_color = sf::Color::Red,
        const sf::Color &in_outlineColor = sf::Color::White,
        float in_outlineThickness = 1.f) noexcept;
};

struct Collision {
  float radius = 0.0f;

  Collision() = default;
  Collision(float in_radius = 0.0f) noexcept;
};

struct Score {
  int score = 0;

  Score() = default;
  Score(int in_score) noexcept;
};

struct LifeSpan {
  int remaining = 0;
  int total = 0;

  LifeSpan() = default;
  LifeSpan(int in_total) noexcept;
};

struct Input {
  bool up = false;
  bool left = false;
  bool right = false;
  bool down = false;
  bool shoot = false;

  Input() noexcept;
};

} // namespace cmp
