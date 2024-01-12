#include "Vec2.hpp"

#include <cmath>

namespace utl {

template <Arithmetic T> Vec2<T>::Vec2() : x(T()), y(T()) {}

template <Arithmetic T> Vec2<T>::Vec2(T in_x, T in_y) : x(in_x), y(in_y) {}

template <Arithmetic T>
auto Vec2<T>::operator==(const Vec2 &rhs) const noexcept -> bool {
  return (x == rhs.x && y == rhs.y);
}

template <Arithmetic T>
auto Vec2<T>::operator!=(const Vec2 &rhs) const noexcept -> bool {
  return !(x == rhs.x && y == rhs.y);
}

template <Arithmetic T>
auto Vec2<T>::operator+(const Vec2<T> &rhs) noexcept -> Vec2<T> {
  return Vec2(x + rhs.x, y + rhs.y);
}

template <Arithmetic T>
auto Vec2<T>::operator-(const Vec2<T> &rhs) noexcept -> Vec2<T> {
  return Vec2(x - rhs.x, y - rhs.y);
}

template <Arithmetic T> auto Vec2<T>::operator*(T rhs) noexcept -> Vec2<T> {
  return Vec2(x * rhs, y * rhs);
}

template <Arithmetic T> auto Vec2<T>::operator/(T rhs) noexcept -> Vec2<T> {
  return Vec2(x / rhs, y / rhs);
}

template <Arithmetic T> void Vec2<T>::operator+=(const Vec2<T> &rhs) noexcept {
  x += rhs.x;
  y += rhs.y;
}

template <Arithmetic T> void Vec2<T>::operator-=(const Vec2<T> &rhs) noexcept {
  x -= rhs.x;
  y -= rhs.y;
}

template <Arithmetic T> void Vec2<T>::operator*=(T rhs) noexcept {
  x *= rhs;
  y *= rhs;
}

template <Arithmetic T> void Vec2<T>::operator/=(T rhs) noexcept {
  x /= rhs;
  y /= rhs;
}

template <Arithmetic T> auto Vec2<T>::getLength() const noexcept {
  return std::sqrt(x * x + y * y);
}

template <Arithmetic T>
auto Vec2<T>::cross(const Vec2 &lhs, const Vec2 &rhs) const noexcept {
  return lhs.x * rhs.y - lhs.y * rhs.x;
}

template <Arithmetic T>
auto Vec2<T>::dot(const Vec2 &lhs, const Vec2 &rhs) const noexcept {
  return lhs.x * rhs.x + lhs.x * rhs.x;
}

template <Arithmetic T>
auto operator<<(std::ostream &os, const Vec2<T> &rhs) -> std::ostream & {
  os << "(" << rhs.x << ", " << rhs.y << ")";
  return os;
}

template <Arithmetic T> auto getUnitVec(const Vec2<T> &vec) {
  auto tmp_x = vec.x / vec.getLength();
  auto tmp_y = vec.y / vec.getLength();

  return Vec2(tmp_x, tmp_y);
}

} // namespace utl
