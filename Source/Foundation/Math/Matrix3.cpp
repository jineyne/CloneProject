#include "Matrix3.hpp"

namespace cpf {
    Matrix3::Matrix3() : m{ 0, } {}
    Matrix3::Matrix3(float val) {
        _11 = _22 = _33 = val;
    }

    float *Matrix3::operator[](uint32_t row) const {
        return (float *)m[row];
    }

    bool Matrix3::operator==(const Matrix3 &rhs) const {
        return equals(rhs);
    }

    bool Matrix3::operator!=(const Matrix3 &rhs) const {
        return !equals(rhs);
    }

    Matrix3 Matrix3::operator+ (const Matrix3 &rhs) const {
        Matrix3 result;

        for (uint32_t i = 0; i < 3; i++) {
            for (uint32_t j = 0; j < 3; j++) {
                result[i][j] = m[i][j] + rhs.m[i][j];
            }
        }

        return result;
    }

    Matrix3 Matrix3::operator- (const Matrix3 &rhs) const {
        Matrix3 result;

        for (uint32_t i = 0; i < 3; i++) {
            for (uint32_t j = 0; j < 3; j++) {
                result[i][j] = m[i][j] - rhs.m[i][j];
            }
        }

        return result;
    }

    Matrix3 Matrix3::operator- () const {
        Matrix3 result;

        for (uint32_t i = 0; i < 3; i++) {
            for (uint32_t j = 0; j < 3; j++) {
                result[i][j] = -m[i][j];
            }
        }

        return result;
    }

    Matrix3 Matrix3::operator* (const Matrix3 &rhs) const {
        Matrix3 result;

        for (uint32_t i = 0; i < 3; i++) {
            for (uint32_t j = 0; j < 3; j++) {
                result[i][j] = (m[i][0] * rhs.m[0][j]) + (m[i][1] * rhs.m[1][j]) + (m[i][2] * rhs.m[2][j]);
            }
        }

        return result;
    }

    bool Matrix3::equals(const Matrix3 &rhs) const {
        for (uint32_t i = 0; i < 3; i++) {
            for (uint32_t j = 0; j < 3; j++) {
                if (m[i][j] != rhs.m[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }
}
