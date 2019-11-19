#pragma once

#include "cpf.hpp"
#include "Math.hpp"

namespace cpf {
    /**
     * 3x3 행렬
     */
    class DLL_EXPORT Matrix3 {
    private:
        union {
            struct {
                float _11, _12, _13;
                float _21, _22, _23;
                float _31, _32, _33;
            };
            float m[3][3];
        };

    public:
        // 행렬 생성자입니다. 모든 인자를 0으로 만듭니다.
        Matrix3();

        /**
         * 행렬 생성자입니다.
         * 1x1 2x2 3x3 에 해당하는 요소를 주어진 인자로 설정합니다.
         */
        Matrix3(float val);

    public:
        /**
         * 행렬의 열을 반환합니다.
         */
        float *operator[](uint32_t row) const;

        bool operator==(const Matrix3 &rhs) const;
        bool operator!=(const Matrix3 &rhs) const;

		Matrix3 operator+ (const Matrix3 &rhs) const;
		Matrix3 operator- (const Matrix3 &rhs) const;
		Matrix3 operator- () const;
		Matrix3 operator* (const Matrix3 &rhs) const;

    public:
        // 주어진 행렬과 요소들이 일치하는지 확인합니다.
        bool equals(const Matrix3 &rhs) const;
    };
}
