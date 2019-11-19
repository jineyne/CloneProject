#pragma once

#include "cpf.hpp"
#include "Math/Math.hpp"

namespace cpf {
    /**
     * 2차원 좌표를 표연하기 위해 사용됩니다.
     */
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
        // Vector 값을 두 사이 값으로 제한시킵니다.
        TVector2 &clamp(TVector2 min, TVector2 max) {
            x = Math::Clamp(x, min.x, max.x);
            y = Math::Clamp(y, min.y, max.y);
            return *this;
        }

        // 해당 좌표와 다른 좌표 사이의 거리를 구합니다.
        float distance(const TVector2 &other) const {
            return std::sqrt((distanceSqured(other)));
        }

        // 해당 좌표와 다른 좌표 사이의 거리의 제곱을 구합니다.
        float distanceSqured(const TVector2 &other) const {
            return (std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
        }

        // 해당 좌표와 다른 좌표의 내적을 구합니다.
        T dot(const TVector2 &other) const {
            return (x * other.x) + (y * other.y);
        }

        // 해당 좌표의 길이를 구합니다.
        float length() const {
            return std::sqrt(lengthSquared());
        }

        // 해당 좌표의 길이의 제곱을 구합니다.
        float lengthSquared() const {
            return (x * x) + (y * y);
        }

        // 해당 좌표를 방향좌표로 만듭니다.
        void normalize() {
            *this = normalized();
        }

        // 해당 좌표의 방향좌표를 구합니다.
        TVector2 normalized() const {
            T factor = lengthSquared();
            if (factor == 0) {
                factor = 1.0f;
            } else {
                factor = 1.0f / std::sqrt(factor);
            }

            return TVector2(x * factor, y * factor);
        }

        // 다른 좌표와 비교합니다.
        bool equals(const TVector2 &other) {
            return x == other.x && y == other.y;
        }
    };

    using IntVector2 = TVector2<int>;
    using Vector2 = TVector2<float>;
}
