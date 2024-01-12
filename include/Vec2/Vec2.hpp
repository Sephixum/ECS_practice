#pragma once

#include <cstdint>
#include <ostream>
#include <type_traits>

namespace utl {

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template <Arithmetic T> class Vec2;

using Vec2f = Vec2<float>;
using Vec2u = Vec2<uint32_t>;
using Vec2d = Vec2<double>;
using Vec2i = Vec2<int>;

template <Arithmetic T> class Vec2 {
public:
  T x = 0;
  T y = 0;

  Vec2();
  Vec2(T in_x, T in_y);
  Vec2(Vec2 &&other) = default;
  Vec2(const Vec2 &other) = default;
  auto operator=(Vec2 &&other) -> Vec2 & = default;
  auto operator=(const Vec2 &other) -> Vec2 & = default;
  ~Vec2() = default;

  auto operator==(const Vec2 &rhs) const noexcept -> bool;
  auto operator!=(const Vec2 &rhs) const noexcept -> bool;

  auto operator+(const Vec2 &rhs) noexcept -> Vec2;
  auto operator-(const Vec2 &rhs) noexcept -> Vec2;
  auto operator*(T rhs) noexcept -> Vec2;
  auto operator/(T rhs) noexcept -> Vec2;

  void operator+=(const Vec2 &rhs) noexcept;
  void operator-=(const Vec2 &rhs) noexcept;
  void operator*=(T rhs) noexcept;
  void operator/=(T rhs) noexcept;

  auto getLength() const noexcept;
  auto cross(const Vec2 &lhs, const Vec2 &rhs) const noexcept;
  auto dot(const Vec2 &lhs, const Vec2 &rhs) const noexcept;

  template <Arithmetic>
  friend auto operator<<(std::ostream &out, const Vec2<T> &rhs)
      -> std::ostream &;

  template<Arithmetic>
  friend auto getUnitVec(const Vec2 &vec);
};

} // namespace utl

#include "Vec2.inl"
