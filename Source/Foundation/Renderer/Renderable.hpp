#pragma once

#include "cpf.hpp"

namespace cpf {
    class DLL_EXPORT Renderable {
    public:
        virtual void render() = 0;
    };
}
