#pragma once

#include "cpf.hpp"
#include "Math.hpp"

namespace cpf {
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
        Matrix3();
        Matrix3(float val);

    public:
        float *operator[](uint32_t row) const;

        bool operator==(const Matrix3 &rhs) const;
        bool operator!=(const Matrix3 &rhs) const;

		Matrix3 operator+ (const Matrix3 &rhs) const;
		Matrix3 operator- (const Matrix3 &rhs) const;
		Matrix3 operator- () const;
		Matrix3 operator* (const Matrix3 &rhs) const;

    public:
        bool equals(const Matrix3 &rhs) const;
    };
}
