#pragma once

#include "cpf.hpp"

namespace cpf {
    class DLL_EXPORT Resource {
    protected:
        String mName;
        uint32_t mSize;

    public:
        Resource();
        virtual ~Resource() = default;

    public:
        const String &getName() const;
        void setName(const String &name);
    };
}
