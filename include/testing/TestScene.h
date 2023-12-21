#pragma once

#include "vortex/objects/Scene.h"
#include "vortex/objects/Sprite.h"

using namespace vortex;

namespace testing {
    class TestScene : public vortex::Scene {
        public:
            Sprite* spr = NULL;

            void ready();
            void update(double delta);
    };
}