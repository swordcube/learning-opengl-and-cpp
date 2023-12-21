#include "vortex/resources/Texture.h"

namespace vortex {
    Texture::~Texture() {
        glDeleteTextures(1, &__id);
        stbi_image_free(pixels);
        pixels = {};
    }

    void Texture::loadFile(const char *filePath) {
        glGenTextures(1, &__id);
        glBindTexture(GL_TEXTURE_2D, __id);

        pixels = stbi_load(filePath, &width, &height, NULL, 4);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    int Texture::getID() {
        return __id;
    }
}