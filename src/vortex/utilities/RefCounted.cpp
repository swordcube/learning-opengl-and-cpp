#include "vortex/utilities/RefCounted.h"

namespace vortex {
    RefCounted::RefCounted() {}
    RefCounted::~RefCounted() {}

    int RefCounted::getReferences() {
        return references;
    }

    void RefCounted::reference() {
        references++;
    }

    void RefCounted::unreference() {
        references--;
        if(references < 1)
            delete this;
    }
}