#pragma once

#include "cpf.hpp"

namespace cpf {
    class DLL_EXPORT RenderTarget {
    public:
        virtual void swapBuffers(uint32_t mask = 0xffffffff) = 0;
    };
}
