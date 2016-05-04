#include "MainLight.hpp"

MainLight::MainLight(std::string pObjectName, glm::vec3 pPosition) : GameObject(pObjectName, pPosition)
{
    light = new Light(this);
}

MainLight::~MainLight()
{

}

float MainLight::getIntensity() const
{
    return light->_intensity;
}

void MainLight::setIntensity(float pIntensity)
{
    light->_intensity = pIntensity;
}

float MainLight::getInnerCone() const
{
    return light->_innerCone;
}

void MainLight::setInnerCone(float pAngle)
{
    light->_innerCone = pAngle;
}

float MainLight::getOuterCone() const
{
    return light->_outerCone;
}

void MainLight::setOuterCone(float pAngle)
{
    light->_outerCone = pAngle;
}

void MainLight::setColor(float r, float g, float b)
{
    light->_color = glm::vec3(r, g, b);
}

void MainLight::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);
}
