#pragma once

#include <glm/vec2.hpp>

namespace vortex {
    class Object {
        public:
            Object();
            virtual ~Object();

            /**
             * The rotation of this object in degrees.
             */
            float angle;

            /**
             * The X and Y coordinates of this object,
             * starting from the top left corner of the screen.
             */
            glm::dvec2 position;

            virtual void update(double delta);
            virtual void draw();
    };
}