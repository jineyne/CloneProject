#pragma once

#include "cpf.hpp"

namespace cpf {
    /**
     * 렌더링이 될 타겟입니다.
     */
    class DLL_EXPORT RenderTarget {
    public:
        // 버퍼를 교체합니다.
        virtual void swapBuffers(uint32_t mask = 0xffffffff) = 0;
    };
}
