#pragma once

#include "cpf.hpp"

#include "Math/Math.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Vector3.hpp"

namespace cpf {
    class DLL_EXPORT Matrix4 {
    private:
        union {
            struct {
                float _11, _12, _13, _14;
                float _21, _22, _23, _24;
                float _31, _32, _33, _34;
                float _41, _42, _43, _44;
            };
            float m[4][4];
        };

    public:
        Matrix4();
        Matrix4(float val);
        Matrix4(const Matrix3 &m);

    public:
        static Matrix4 Translation(const Vector3 &position);
        static Matrix4 Rotation(const Quaternion &rotation);
        static Matrix4 Scaling(const Vector3 &scale);
        static Matrix4 Perspective(float fov, float aspect, float near, float far);
        static Matrix4 Orthograhic(float left, float right, float bottom, float top, float near, float far);

    public:
        float *operator[](uint32_t row) const;

        Matrix4 operator*(const Matrix4 &rhs) const;
    };
}
