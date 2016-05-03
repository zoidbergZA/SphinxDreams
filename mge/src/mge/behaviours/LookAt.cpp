#include <glm.hpp>
#include "mge/behaviours/LookAt.hpp"
#include "mge/core/GameObject.hpp"

#include <iostream>

LookAt::LookAt(GameObject * pTarget, GameObject* pOwner): AbstractBehaviour(), _target(pTarget) {
    addBehaviourToGO(pOwner);
}

LookAt::~LookAt() {
    //dtor
}

void LookAt::addBehaviourToGO(GameObject* pGameObject) {
    pGameObject->addBehaviour(this);
}

/**
 * Looks at the given target
 */

void LookAt::update( float step ) {
    //two ways of doing the same thing:
    //Through GLM
    /*
    _owner->setTransform(
        glm::inverse (
            glm::lookAt (_owner->getWorldPosition(), _target->getWorldPosition(), glm::vec3(0,1,0))
        )
    );
    */

    //manually
    //the other way then you would expect, the camera is flipped over the z axis we are staring out of its a.. basically ;)
    //this is due to how the perspective matrix is set up
    glm::vec3 forward = glm::normalize(_owner->getLocalPosition() - _target->getLocalPosition());
    glm::vec3 right = glm::cross (glm::vec3(0,1,0), forward);
    glm::vec3 up = glm::cross (forward, right);

    _owner->setTransform(
      glm::mat4 (glm::vec4(right,0), glm::vec4(up,0), glm::vec4(forward,0), glm::vec4(_owner->getLocalPosition(),1) )
    );
}
