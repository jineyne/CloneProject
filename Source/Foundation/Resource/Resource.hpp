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
        virtual size_t hash() const;

        const String &getName() const;
        void setName(const String &name);
    };
}

namespace std {
    template<>
    struct hash<cpf::Resource> {
        size_t operator()(const cpf::Resource &resource) const {
            return resource.hash();
        }
    };
}
