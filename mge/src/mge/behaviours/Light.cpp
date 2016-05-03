#include "Light.hpp"
#include "GameObject.hpp"

Light::Light(GameObject* pOwner)
{
    addBehaviourToGO(pOwner);

    _color = glm::vec3(1.0f, 1.0f, 0.7f);
    _intensity = 0.85f;
    _innerCone = 15.0f;
    _outerCone = 29.0f;
}

Light::~Light()
{

}

glm::vec3 Light::getColor() const
{
    return _color;
}

float Light::getIntensity() const
{
    return _intensity;
}

float Light::getInnerCone() const
{
    return _innerCone;
}

float Light::getOuterCone() const
{
    return _outerCone;
}

void Light::addBehaviourToGO(GameObject* pGameObject)
{
    pGameObject->addBehaviour(this);
}

void Light::update(float step)
{
//    getOwner()->yaw(20.0f * step);
}
