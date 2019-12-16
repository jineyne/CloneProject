#pragma once

#include "cpf.hpp"

#include "RenderAPI/Buffer.hpp"

namespace cpf {
    enum class ETextureType {
        e2D,
    };

    enum class ETextureUsage {
        Static = static_cast<uint32_t>(BufferUsage::Static),
        Dynamic = static_cast<uint32_t>(BufferUsage::Dynamic),

        Default = static_cast<uint32_t>(ETextureUsage::Static),
    };

    using TextureData = std::vector<char>;

    struct TextureCreateInfo {
        ETextureType type = ETextureType::e2D;
        uint32_t width;
        uint32_t height;
        uint32_t depth;
        uint32_t mipsCount = 0;
        TextureData initialData;
        ETextureUsage usage = ETextureUsage::Default;
    };

    class DLL_EXPORT Texture {
    private:
        TextureCreateInfo mInfo;
        uint32_t mTextureId;

    public:
        Texture(const TextureCreateInfo &info);

    public:
        void initialize();

        void write(const TextureData &data);
        void write(const uint8_t *buf);

        uint32_t getWidth() const { return mInfo.width; }
        uint32_t getHeight() const { return mInfo.height; }
        uint32_t getDepth() const { return mInfo.depth; }

        uint32_t getTextureId() const { return mTextureId; }
    };
}
