#pragma once

#include "cpf.hpp"

namespace cpf {
    template <typename Enum, typename Storage = uint32_t>
    class DLL_EXPORT Flags {
    private:
        using ThisType = Flags<Enum, Storage>;
        Storage mFlags = 0;

    public:
        Flags() = default;
        Flags(Storage flags) : mFlags(flags) {}
        Flags(Enum val) : mFlags(static_cast<Storage>(val)) {}
        Flags(ThisType &val) : mFlags(val.mFlags) {}

    public:
        operator bool() const {
            return mFlags != 0;
        }

    public:
        ThisType &set(Enum val) {
            mFlags |= static_cast<Storage>(val);

            return *this;
        }

        bool isSet(Enum val) {
            return (mFlags & static_cast<Storage>(val)) == static_cast<Storage>(val);
        }

        void unSet(Enum val) {
            mFlags &= ~static_cast<Storage>(val);
        }

        bool equals(const ThisType &rhs) const {
            return mFlags == rhs.mFlags;
        }
    };
}
