#pragma once

#include "cpf.hpp"

#include "Math/Math.hpp"
#include "Math/Matrix3.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Vector3.hpp"

namespace cpf {
    /**
     * 4x4 행렬
     */
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
        // 행렬 기본 생성자입니다. 모든 요소를 0으로 초기화합니다.
        Matrix4();
        // 행렬 기본 생성자입니다. 요소를 주어진 값으로 초기화합니다.
        Matrix4(float val);

        Matrix4(const Matrix3 &m);

    public:
        // 주어진 위치를 기반으로 행렬을 생성합니다.
        static Matrix4 Translation(const Vector3 &position);

        // 주어진 회전 값을 기반으로 행렬을 생성합니다.
        static Matrix4 Rotation(const Quaternion &rotation);

        // 주어진 크기를 기반으로 행렬을 생성합니다.
        static Matrix4 Scaling(const Vector3 &scale);

    public:
        float *operator[](uint32_t row) const;

        Matrix4 operator*(const Matrix4 &rhs) const;

    };
}
