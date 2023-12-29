#pragma once

#include "Vec2/Vec2.hpp"

#include <SFML/Graphics/CircleShape.hpp>

class CTransform {
public:
  Util::Vec2f pos = {0.0f, 0.0f};
  Util::Vec2f velocity = {0.0f, 0.0f};
  float angle = 0.0f;

  CTransform(const Util::Vec2f &in_pos, const Util::Vec2f &in_velocity,
             float in_angle) noexcept;
};

class CShape {
public:
  sf::CircleShape shape;

  CShape(float in_radius, int in_sides,
         const sf::Color &in_color = sf::Color::Green,
         const sf::Color &in_outlineColor = sf::Color::White,
         float in_thickness = 0.f) noexcept;
};

class CCollision {
public:
  float radius = 0.0f;

  CCollision(float in_radius) noexcept;
};

class CScore {
public:
  int score = 0;

  CScore(int in_score) noexcept;
};

class CLifeSpan {
public:
  int remaining = 0;
  int total = 0;

  CLifeSpan(int in_total) noexcept;
};

class CInput {
public:
  bool up = false;
  bool left = false;
  bool right = false;
  bool down = false;
  bool shoot = false;

  CInput() noexcept;
};