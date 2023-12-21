#pragma once

#include <glad/glad.h>
#include <map>
#include "vortex/resources/Texture.h"

namespace vortex {
    class AssetServer {
        public:
            static std::map<const char*, void*> cache;
            
            static void init();
            static Texture* loadTexture(const char *filePath);
    };
}