#include <stdlib.h>
#include "vortex/objects/Object.h"

namespace vortex {
    Object::Object() {
        angle = 0.0;
        position = glm::dvec2(0.0, 0.0);
    }

    Object::~Object() {}

    void Object::update(double delta) {}
    void Object::draw() {}
}