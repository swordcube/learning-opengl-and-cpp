#include "vortex/utilities/Tools.h"
#include "vortex/servers/AssetServer.h"
#include <string.h>

using namespace vortex;

namespace vortex {
    std::map<const char*, void*> AssetServer::cache;

    void AssetServer::init() {
        cache = {};
    }

    Texture* AssetServer::loadTexture(const char* filePath) {
        const char *assetKey = Tools::concatString("#_IMAGE_", filePath);
        if(cache[assetKey] == NULL) {
            Texture* texture = new Texture();
            texture->loadFile(filePath);
            cache[assetKey] = texture;
        }
        return (Texture*)cache[assetKey];
    }
}