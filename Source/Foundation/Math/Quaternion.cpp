#include "Quaternion.hpp"

namespace cpf {
    Quaternion::Quaternion(float val) : x(val), y(val), z(val), w(val) {}

    void Quaternion::fromAxisAngle(const Vector3 &axis, float radian) {
        float half = 0.5f * radian;
        float s = std::sin(half);

        x = s * axis.x;
        y = s * axis.y;
        z = s * axis.z;
        w = std::cos(half);
    }

    void Quaternion::fromAxis(const Vector3 &xAxis, const Vector3 &yAxis, const Vector3 &zAxis) {
        // TODO:
    }

    void Quaternion::fromEulerAngles(float xAngle, float yAngle, float &zAngle) {
        float halfX = xAngle * 0.5f;
        float halfY = yAngle * 0.5f;
        float halfZ = zAngle * 0.5f;

        float cx = std::cos(halfX);
        float sx = std::sin(halfX);

        float cy = std::cos(halfY);
        float sy = std::sin(halfY);

        float cz = std::cos(halfZ);
        float sz = std::sin(halfZ);

        Quaternion quatX(sx, 0.0f, 0.0f, cx);
        Quaternion quatY(0.0f, sy, 0.0f, cy);
        Quaternion quatZ(0.0f, 0.0f, sz, cz);

        *this = quatZ * (quatX * quatY);
    }

    Quaternion Quaternion::inverse() const {
        float fNorm = x * x + y * y + z * z + w * w;
        if (fNorm > 0.0f) {
            float fInvNorm = 1.0f / fNorm;
            return Quaternion(-x * fInvNorm, -y * fInvNorm, -z * fInvNorm, w * fInvNorm);
        } else {
            return Quaternion();
        }
    }
}
