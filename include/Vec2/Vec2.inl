#include "Vec2.hpp"

namespace Util
{

    template <Arithmetic T>
    Vec2<T>::Vec2() : x(T()), y(T()) {}

    template <Arithmetic T>
    Vec2<T>::Vec2(T in_x, T in_y) : x(in_x), y(in_y) {}

    template <Arithmetic T>
    auto Vec2<T>::operator==(const Vec2 &rhs) const noexcept -> bool
    {
        return (x == rhs.x && y == rhs.y);
    }

    template <Arithmetic T>
    auto Vec2<T>::operator!=(const Vec2 &rhs) const noexcept -> bool
    {
        return !(x == rhs.x && y == rhs.y);
    }

    template <Arithmetic T>
    auto Vec2<T>::operator+(const Vec2<T> &rhs) noexcept -> Vec2<T>
    {
        return Vec2(x + rhs.x, y + rhs.y);
    }

    template <Arithmetic T>
    auto Vec2<T>::operator-(const Vec2<T> &rhs) noexcept -> Vec2<T>
    {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    template <Arithmetic T>
    auto Vec2<T>::operator*(T rhs) noexcept -> Vec2<T>
    {
        return Vec2(x * rhs.x, y * rhs.y);
    }

    template <Arithmetic T>
    auto Vec2<T>::operator/(T rhs) noexcept -> Vec2<T>
    {
        return Vec2(x / rhs.x, y / rhs.m_y);
    }

    template <Arithmetic T>
    void Vec2<T>::operator+=(const Vec2<T> &rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
    }

    template <Arithmetic T>
    void Vec2<T>::operator-=(const Vec2<T> &rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
    }

    template <Arithmetic T>
    void Vec2<T>::operator*=(T rhs) noexcept
    {
        x *= rhs;
        y *= rhs;
    }

    template <Arithmetic T>
    void Vec2<T>::operator/=(T rhs) noexcept
    {
        x /= rhs;
        y /= rhs;
    }

    template <Arithmetic T>
    auto Vec2<T>::getLength() const noexcept
    {
        return std::sqrt(x * x + y * y);
    }

    template <Arithmetic T>
    auto Vec2<T>::cross(const Vec2 &lhs, const Vec2 &rhs) const noexcept
    {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

    template <Arithmetic T>
    auto Vec2<T>::dot(const Vec2 &lhs, const Vec2 &rhs) const noexcept
    {
        return lhs.x * rhs.x + lhs.x * rhs.x;
    }

    template <Arithmetic T>
    auto operator<<(std::ostream &os, const Vec2<T> &rhs) -> std::ostream &
    {
        os << rhs.x << ' ' << rhs.y;
        return os;
    }

}