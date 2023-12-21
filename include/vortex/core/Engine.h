#pragma once

#define VORTEX_WINDOW_WIDTH 640
#define VORTEX_WINDOW_HEIGHT 480

#include "vortex/objects/Sprite.h"
#include "vortex/servers/AssetServer.h"
#include "vortex/servers/RenderingServer.h"
#include "vortex/objects/Scene.h"

namespace vortex {
    class Engine {
        public:
            static void init(Scene* initialScene);

            static Scene* getCurrentScene();
            static void setCurrentScene(Scene* newScene);

        private:
            static Scene* currentScene;
    };
}