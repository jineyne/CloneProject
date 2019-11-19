#pragma once

#include "cpf.hpp"

namespace cpf {
    /**
     * 기타 수학 함수들입니다.
     */
    class Math {
    public:
        static double PI;

        /**
         * 값을 최솟값과 최대값 사이로 제한합니다.
         * @param val 제한시킬 값
         */
        template <typename T>
        static T Clamp(T val, T min, T max) {
            val = Max(val, min);
            val = Min(val, max);
        }

        /**
         * min max 사이중 amount 만큼의 위치를 계산합니다.
         */
        template <typename T>
        static T Lerp(T min, T max, T amount) {
            return min + (max - min) * amount;
        }

        // 두 값중 최대값을 구합니다.
        template <typename T>
        static T Max(T a, T b) {
            return (a > b) ? a : b;
        }

        // 두 값중 최소값을 구합니다.
        template <typename T>
        static T Min(T a, T b) {
            return (a > b) ? b : a;
        }
    };
}
