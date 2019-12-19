#include "Resource.hpp"

namespace cpf {
    Resource::Resource() {
    }

    size_t Resource::hash() const {
        std::hash<String> hs;

        return hs(mName);
    }

    const String &Resource::getName() const {
        return mName;
    }

    void Resource::setName(const String &name) {
        mName = name;
    }
}
