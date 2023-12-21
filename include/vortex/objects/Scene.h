#pragma once

#include <vector>
#include "vortex/objects/Object.h"

namespace vortex {
    class Scene : public Object {
        public:
            virtual void ready();

            virtual void add(Object* object);
            virtual void insert(int position, Object* object);
            virtual void remove(Object* object, bool splice = false);

            void update(double delta);
            void draw();

            std::vector<Object*> members;
    };
}