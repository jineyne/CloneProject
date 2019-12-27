#pragma once

#include "cpf.hpp"
#include "Math/Math.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Vector3.hpp"

namespace cpf {
    class DLL_EXPORT Quaternion {
    public:
        float x, y, z, w;

    public:
        Quaternion(float value = 0.0f);

        Quaternion(float x, float y, float z, float w) 
            : x(x), y(y), z(z), w(w) {}

        Quaternion(const Vector3 &axis, float angle) {
            fromAxisAngle(axis, angle);
        }

        Quaternion(float xAngle, float yAngle, float zAngle) {
            fromEulerAngles(xAngle, yAngle, zAngle);
        }

    public:
        void fromAxisAngle(const Vector3 &axis, float radian);
        void fromAxis(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis);
        void fromEulerAngles(float xAngle, float yAngle, float &zAngle);

        Quaternion operator+ (const Quaternion &rhs) const {
            return Quaternion(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
        }

        Quaternion operator-(const Quaternion &rhs) const {
            return Quaternion(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.z);
        }

        Quaternion operator*(const Quaternion &rhs) const {
            return Quaternion (
                    w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
                    w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
                    w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x,
                    w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z
            );
        }

        Quaternion operator*(float rhs) const {
            return Quaternion(rhs * x, rhs * y, rhs * z, rhs * w);
        }

        Quaternion operator/(float rhs) const {
            assert(rhs != 0.0);

            float inv = 1.0f / rhs;
            return Quaternion(x * inv, y * inv, z * inv, w * inv);
        }

        Quaternion operator-() const {
            return Quaternion(-x, -y, -z, -w);
        }

        bool operator==(const Quaternion &rhs) const {
            return (x == rhs.x) && (y == rhs.y) && (z == rhs.z) && (w == rhs.w);
        }

        bool operator!=(const Quaternion &rhs) const {
            return !(*this == rhs);
        }

        Quaternion &operator+=(const Quaternion &rhs) {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            w += rhs.w;

            return *this;
        }

        Quaternion &operator-=(const Quaternion &rhs) {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            w -= rhs.w;

            return *this;
        }

        Quaternion &operator*=(const Quaternion &rhs) {
            float newX = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
            float newY = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
            float newZ = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
            float newW = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;

            x = newX; y = newY; z = newZ; w = newW;

            return *this;
        }

        friend Quaternion operator*(float lhs, const Quaternion &rhs) {
            return Quaternion(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
        }

    public:
        float dot(const Quaternion &quat) const {
            return x * quat.x + y * quat.y + z * quat.z + w * quat.w;
        }

        float normalize(float tolerance = 1e-04f) {
            float len = std::sqrt(dot(*this));
            if (len > (tolerance * tolerance)) {
                *this = *this *(1.0f / len);
            }

            return len;
        }

        Quaternion inverse() const;

        Matrix3 toRotationMatrix() const;
    };
}
