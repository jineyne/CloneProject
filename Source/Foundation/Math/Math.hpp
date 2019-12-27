#pragma once

#include "cpf.hpp"

namespace cpf {
    class Math {
    public:
        static double PI;

        template <typename T>
        static T Clamp(T val, T min, T max) {
            val = Max(val, min);
            val = Min(val, max);
        }

        template <typename T>
        static T Lerp(T min, T max, T amount) {
            return min + (max - min) * amount;
        }

        template <typename T>
        static T Max(T a, T b) {
            return (a > b) ? a : b;
        }

        template <typename T>
        static T Min(T a, T b) {
            return (a > b) ? b : a;
        }
    };
}
