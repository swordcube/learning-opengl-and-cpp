#include "vortex/core/Engine.h"
#include "testing/TestScene.h"

using namespace vortex;

int main() {
    Engine::init(new testing::TestScene());
    return 0;
}