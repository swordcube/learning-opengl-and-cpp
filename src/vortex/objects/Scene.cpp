#include <algorithm>
#include "vortex/utilities/Tools.h"
#include "vortex/objects/Scene.h"
#include <stdio.h>

namespace vortex {
    void Scene::ready() {}

    void Scene::add(Object* object) {
        // // If the members list already contains this object, don't add it again.
        std::vector<Object*>::iterator it = std::find(members.begin(), members.end(), object);
        int index = std::distance(members.begin(), it);
        if(members.size() > 0 && !Tools::isNull(members[index]))
            return;

        members.push_back(object);
    }

    void Scene::insert(int position, Object* object) {
        // If the members list already contains this object, don't add it again.
        std::vector<Object*>::iterator it = std::find(members.begin(), members.end(), object);
        int index = std::distance(members.begin(), it);
        if(position >= members.size() || (members.size() > 0 && !Tools::isNull(members[index])))
            return;

        members.insert(members.begin() + position, object);
    }

    void Scene::remove(Object* object, bool splice) {
        // If the members list already doesn't have this object, don't remove it again.
        std::vector<Object*>::iterator it = std::find(members.begin(), members.end(), object);
        int index = std::distance(members.begin(), it);
        if(members.size() > 0 && Tools::isNull(members[index]))
            return;

        if(splice)
            members.erase(it);
        else
            members[index] = NULL;
    }

    void Scene::update(double delta) {
        for(int i = 0; i < members.size(); i++) {
            Object* obj = members[i];
            if(!Tools::isNull(obj))
                obj->update(delta);
        }
    }

    void Scene::draw() {
        for(int i = 0; i < members.size(); i++) {
            Object* obj = members[i];
            if(!Tools::isNull(obj))
                obj->draw();
        }
    }
}