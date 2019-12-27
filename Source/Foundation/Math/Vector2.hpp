#pragma once

#include "cpf.hpp"
#include "Math/Math.hpp"

namespace cpf {
    template <typename T> class TVector2 {
    public:
       T x{0};
       T y{0};

    public:
        TVector2(T val) : x(val), y(val) {}
        TVector2(T x, T y) : x(x), y(y) {}

    public:
        TVector2 operator+(const TVector2 &rhs) const {
            return TVector2(x + rhs.x, y + rhs.y);
        }

        TVector2 operator-(const TVector2 &rhs) const {
            return TVector2(x - rhs.x, y - rhs.y);
        }

        TVector2 operator*(const TVector2 &rhs) const {
            return TVector2(x * rhs.x, y * rhs.y);
        }

        TVector2 operator/(const TVector2 &rhs) const {
            return TVector2(x / rhs.x, y / rhs.y);
        }

        TVector2 &operator+=(const TVector2 &rhs) {
            *this = *this + rhs;
            return *this;
        }

        TVector2 &operator-=(const TVector2 &rhs) {
            *this = *this - rhs;
            return *this;
        }

        TVector2 &operator*=(const TVector2 &rhs) {
            *this = *this * rhs;
            return *this;
        }

        TVector2 &operator/=(const TVector2 &rhs) {
            *this = *this / rhs;
            return *this;
        }

    public:
        TVector2 &clamp(TVector2 min, TVector2 max) {
            x = Math::Clamp(x, min.x, max.x);
            y = Math::Clamp(y, min.y, max.y);
            return *this;
        }

        float distance(const TVector2 &other) const {
            return std::sqrt((distanceSqured(other)));
        }

        float distanceSqured(const TVector2 &other) const {
            return (std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
        }

        T dot(const TVector2 &other) const {
            return (x * other.x) + (y * other.y);
        }

        float length() const {
            return std::sqrt(lengthSquared());
        }

        float lengthSquared() const {
            return (x * x) + (y * y);
        }

        void normalize() {
            *this = normalized();
        }

        TVector2 normalized() const {
            T factor = lengthSquared();
            if (factor == 0) {
                factor = 1.0f;
            } else {
                factor = 1.0f / std::sqrt(factor);
            }

            return TVector2(x * factor, y * factor);
        }

        bool equals(const TVector2 &other) {
            return x == other.x && y == other.y;
        }
    };

    using IntVector2 = TVector2<int>;
    using Vector2 = TVector2<float>;
}
