#include "vortex/servers/AssetServer.h"
#include "testing/TestScene.h"

using namespace vortex;

namespace testing {
    Sprite* spr;

    void TestScene::ready() {
        spr = new Sprite();
        spr->setTexture(AssetServer::loadTexture("assets/sonic.png"));
        spr->origin.x = 0.5;
        spr->origin.y = 0.5;
        spr->scale.x = 0.3;
        spr->scale.y = 0.3;
        spr->position.x += (spr->getTexture()->width * spr->scale.x) * 0.5;
        spr->position.y += (spr->getTexture()->height * spr->scale.x) * 0.5;
        add(spr);
    }

    void TestScene::update(double delta) {
        Scene::update(delta);
        spr->angle += delta * 120;
    }
}