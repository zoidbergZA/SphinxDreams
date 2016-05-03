#include <cassert>
#include <algorithm>
#include <iostream>

#include "AbstractGame.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/BaseLight.h"
#include "MeshRenderer.hpp"

using namespace std;

std::vector<BaseLight*> _lights;

// Global static pointer used to ensure a single instance of the class.
World* World::_instance = NULL;

World* World::Instance()
{
   if (!_instance)   // Only allow one instance of class to be generated.
      _instance = new World;

   return _instance;
}


World::World():GameObject("root", glm::vec3(0,0,0), false), _mainCamera(0)
{
    ambient = glm::vec3(0.27f, 0.26f, 0.20f);
}

void World::setMainCamera (Camera* pCamera) {
    if (pCamera != NULL) _mainCamera = pCamera;
}

Camera* World::getMainCamera () {
    return _mainCamera;
}

void World::renderDebugInfo() {
    //walk through all meshes and debug their normals
    GameObject* gameObject;
    for (int i = 0; i < getChildCount(); i++) {
        gameObject = getChildAt(i);
//        std::cout << gameObject->getName() << std::endl;
        //oo wise it would be better to do gameObject->renderDebugInfo, but since this is only for debugging
        //it's sort of pasted on
        MeshRenderer* mr = gameObject->getBehaviour<MeshRenderer>();
        if (mr != NULL)
        {
            if (mr->getMaterial() && mr->getMesh() && RENDERDEBUG)
            {
                mr->getMesh()->renderDebugInfo(gameObject->getWorldTransform(), this);
            }
        }
    }
}

void World::addLight(BaseLight* light)
{
    _lights.push_back(light);
}

