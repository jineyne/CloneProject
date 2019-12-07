#pragma once

#include "cpf.hpp"

namespace cpf {
    class DLL_EXPORT Renderable {
    public:
        Renderable();
        virtual ~Renderable();
    public:
        virtual void render() = 0;
    };
}
