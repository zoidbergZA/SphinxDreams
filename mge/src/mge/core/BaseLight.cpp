#include "BaseLight.h"

BaseLight::BaseLight(glm::vec3 pAmbientColor, float pAmbientIntensity, glm::vec3 pConeDirection,
                     float pConeAngle, GameObject* pOwner): AbstractBehaviour() {
    addBehaviourToGO(pOwner);
    ambientColor = pAmbientColor;
    ambientIntensity = pAmbientIntensity;
    coneDirection = pConeDirection;
    coneAngle = pConeAngle;
    World::Instance()->addLight(this);
}

BaseLight::~BaseLight() {
    //dtor
}

void BaseLight::addBehaviourToGO(GameObject* pGameObject) {
    pGameObject->addBehaviour(this);
}

void BaseLight::update(float pStep) {
}
