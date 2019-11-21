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
            {0.0f, 0.0f, 0.0f, 0.0f}}{}

    Matrix4 Matrix4::Translation(const Vector3 &position) {
        Matrix4 m(1);

        m[0][3] = position.x; 
        m[1][3] = position.y;
        m[2][3] = position.z;

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

    float *Matrix4::operator[](uint32_t row) const {
        return (float *)m[row];
    }

    Matrix4 Matrix4::operator *(const Matrix4 &rhs) const {
        Matrix3 result;

        for (uint32_t i = 0; i < 4; i++) {
            for (uint32_t j = 0; j < 4; j++) {
                result[i][j] = (m[i][0] * rhs.m[0][j]) + (m[i][1] * rhs.m[1][j]) + (m[i][2] * rhs.m[2][j]) + 
                    (m[i][3] * rhs.m[3][j]);
            }
        }

        return result;
    }
}
