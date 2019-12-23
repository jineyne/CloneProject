#include "Matrix4.hpp"

namespace cpf {
    Matrix4::Matrix4() : m{0, } {}

    Matrix4::Matrix4(float val) : m{0,} {
        _11 = _22 = _33 = _44 = val;
    }

    Matrix4::Matrix4(const Matrix3 &m)
        : m{{m[0][0], m[0][1], m[0][2], 0.0f},
            {m[1][0], m[1][1], m[1][2], 0.0f},
            {m[2][0], m[2][1], m[2][2], 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}}{}

    Matrix4 Matrix4::Translation(const Vector3 &position) {
        Matrix4 m(1);

        m[3][0] = position.x;
        m[3][1] = position.y;
        m[3][2] = position.z;

        return m;
    }

    Matrix4 Matrix4::Rotation(const Quaternion &rotation) {
        return Matrix4(rotation.toRotationMatrix());
    }

    Matrix4 Matrix4::Scaling(const Vector3 &scale) {
        Matrix4 m(1);

        m[0][0] = scale.x;
        m[1][1] = scale.y;
        m[2][2] = scale.z;

        return m;
    }

    Matrix4 Matrix4::Perspective(float fov, float aspect, float near, float far) {
        float q = 1.0f / tan(fov / 2.0f);
        float a = q / aspect;

        float b = -(far + near) / (far - near);
        float c = -(2 * far * near) / (far - near);

        Matrix4 result(1.0f);

        result._11 = a;
        result._22 = q;
        result._33 = b;
        result._34 = -1.0f;
        result._43 = c;

        return result;
    }

    Matrix4 Matrix4::Orthograhic(float left, float right, float bottom, float top, float near, float far) {
        Matrix4 result(1.0f);

        result._11 = static_cast<float>(2) / (right - left);
        result._22 = static_cast<float>(2) / (top - bottom);
        result._33 = -static_cast<float>(2) / (far - near);
        result._41 = -(right + left) / (right - left);
        result._42 = -(top + bottom) / (top - bottom);
        result._43 = -(far + near) / (far - near);

        return result;
    }

    float *Matrix4::operator[](uint32_t row) const {
        return (float *)m[row];
    }

    Matrix4 Matrix4::operator *(const Matrix4 &rhs) const {
        Matrix4 result;

        for (uint32_t i = 0; i < 4; i++) {
            for (uint32_t j = 0; j < 4; j++) {
                result[i][j] = (m[i][0] * rhs.m[0][j]) + (m[i][1] * rhs.m[1][j]) + (m[i][2] * rhs.m[2][j]) + 
                    (m[i][3] * rhs.m[3][j]);
            }
        }

        return result;
    }
}
