#include "Resource.hpp"

namespace cpf {
    Resource::Resource() {
    }

    const String &Resource::getName() const {
        return mName;
    }

    void Resource::setName(const String &name) {
        mName = name;
    }
}
