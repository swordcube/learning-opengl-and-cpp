#pragma once

#include "vortex/core/Shader.h"
#include "vortex/objects/Object.h"
#include "vortex/resources/Texture.h"

namespace vortex {
    class Sprite : public Object {
        public:
            /**
             * The origin of this sprite for rotation.
             */
            glm::dvec2 origin;

            /**
             * The X and Y scale multiplier of this sprite.
             */
            glm::dvec2 scale;

            Sprite();
            ~Sprite();

            Texture* getTexture();
            Shader* getShader();
            void setTexture(Texture* newTexture);
            void setShader(Shader* newShader);

            void update(double delta);
            void draw();

        private:
            Shader* shader = NULL;
            Texture* texture = NULL;
    };
}