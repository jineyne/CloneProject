#pragma once

#include "cpf.hpp"
#include "Math/Math.hpp"
#include "Math/Vector2.hpp"

namespace cpf {
    template <typename T> class TVector3 {
    public:
        T x{0};
		T y{0};
        T z{0};

    public:
        TVector3(T val) : x(val), y(val), z(val) {}
        TVector3(TVector2<T> vec, T z) : x(vec.x), y(vec.y), z(z) {}
        TVector3(T x, T y, T z) : x(x), y(y), z(z) {}

    public:
        TVector3 operator+(const TVector3 &rhs) const {
            return TVector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        TVector3 operator-(const TVector3 &rhs) const {
            return TVector3(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        TVector3 operator*(const TVector3 &rhs) const {
            return TVector3(x * rhs.x, y * rhs.y, z * rhs.z);
        }

        TVector3 operator/(const TVector3 &rhs) const {
            return TVector3(x / rhs.x, y / rhs.y, z / rhs.z);
        }

        TVector3 &operator+=(const TVector3 &rhs) {
            *this = *this + rhs;
            return *this;
        }

        TVector3 &operator-=(const TVector3 &rhs) {
            *this = *this - rhs;
            return *this;
        }

        TVector3 &operator*=(const TVector3 &rhs) {
            *this = *this * rhs;
            return *this;
        }

        TVector3 &operator/=(const TVector3 &rhs) {
            *this = *this / rhs;
            return *this;
        }

    public:
        TVector3 &clamp(TVector3 min, TVector3 max) {
            x = Math::Clamp(x, min.x, max.x);
            y = Math::Clamp(y, min.y, max.y);
            z = Math::Clamp(z, min.z, max.z);
            return *this;
        }
        
        TVector3 cross(const TVector3 &rhs) const {
            return TVector3(
                    y * rhs.z - z * rhs.y,
                    -(x * rhs.z - z * rhs.x),
                    x * rhs.y - y * rhs.x);
        }

        float distance(const TVector3 &other) const {
            return std::sqrt((distanceSqured(other)));
        }

        float distanceSqured(const TVector3 &other) const {
            return (std::pow(x - other.x, 2) + std::pow(y - other.y, 2) + std::pow(z - other.z, 2));
        }

        T dot(const TVector3 &other) const {
            return (x * other.x) + (y * other.y) + (z * other.z);
        }

        float length() const {
            return std::sqrt(lengthSquared());
        }

        float lengthSquared() const {
            return (x * x) + (y * y) + (z * z);
        }

        void normalize() {
            *this = normalized();
        }

        TVector3 normalized() const {
            T factor = lengthSquared();
            if (factor == 0) {
                factor = 1.0f;
            } else {
                factor = 1.0f / std::sqrt(factor);
            }

            return TVector3(x * factor, y * factor, z * factor);
        }

        bool equals(const TVector3 &other) {
            return x == other.x && y == other.y && z == other.z;
        }
    };

    using IntVector3 = TVector3<int>;
    using Vector3 = TVector3<float>;
}
