#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "vortex/utilities/RefCounted.h"

namespace vortex {
    class Texture : public RefCounted {
        public:
            ~Texture();

            int width = 0;
            int height = 0;
            unsigned char* pixels = {};

            void loadFile(const char *filePath);
            int getID();

        private:
            unsigned int __id = -1;
    };
}