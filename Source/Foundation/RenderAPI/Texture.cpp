#include "Texture.hpp"

namespace cpf {
    Texture::Texture(const TextureCreateInfo &info) : mInfo(info) {}

    void Texture::initialize() {
        glGenTextures(1, &mTextureId);

        glBindTexture(GL_TEXTURE_2D, mTextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if (!mInfo.initialData.empty()) {
            write(mInfo.initialData);
        }
    }

    void Texture::write(const TextureData &data) {
        glBindTexture(GL_TEXTURE_2D, mTextureId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mInfo.width, mInfo.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data());
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    void Texture::write(const uint8_t *buf) {
        glBindTexture(GL_TEXTURE_2D, mTextureId);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mInfo.width, mInfo.height, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}
