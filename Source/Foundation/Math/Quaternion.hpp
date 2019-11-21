#pragma once

#include "cpf.hpp"
#include "Math/Math.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Vector3.hpp"

namespace cpf {
    /**
     * 사원소(Quaternion)은 회전을 표현하기 위해 사용됩니다.
     */
    class DLL_EXPORT Quaternion {
    public:
        float x, y, z, w;

    public:
        /**
         * 원소들을 주어진 인자로 초기화한다.
         */
        Quaternion(float value = 0.0f);

        /**
         * 원소들을 주어진 인자들로 초기화한다.
         */
        Quaternion(float x, float y, float z, float w) 
            : x(x), y(y), z(z), w(w) {}

        /**
         * 원소들을 주어진 AxisAngle로 초기화한다.
         */
        Quaternion(const Vector3 &axis, float angle) {
            fromAxisAngle(axis, angle);
        }

        /**
         * 원소들을 주어진 EulerAngle들로 초기화한다.
         */
        Quaternion(float xAngle, float yAngle, float zAngle) {
            fromEulerAngles(xAngle, yAngle, zAngle);
        }

    public:
        /**
         * Axis 앵글로 Quaternion을 초기화합니다.
         */
        void fromAxisAngle(const Vector3 &axis, float radian);
        // Axis 앵글로 Quaternion을 초기화합니다.
        void fromAxis(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis);
        // Euler 앵글로 Quaternion을 초기화합니다.
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
        // 주어진 quaternion과 내적을 계산합니다.
        float dot(const Quaternion &quat) const {
            return x * quat.x + y * quat.y + z * quat.z + w * quat.w;
        }

        // quaternion을 정규하합니다.
        float normalize(float tolerance = 1e-04f) {
            float len = std::sqrt(dot(*this));
            if (len > (tolerance * tolerance)) {
                *this = *this *(1.0f / len);
            }

            return len;
        }

        // quaternion을 반전시킵니다.
        Quaternion inverse() const;

        // 해당 quaternion을 회전 행렬로 변환합니다.
        Matrix3 toRotationMatrix() const;
    };
}
