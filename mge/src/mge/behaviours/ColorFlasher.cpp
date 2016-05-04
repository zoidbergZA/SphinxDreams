#include "ColorFlasher.hpp"

#include <iostream>

#include "mge/core/GameObject.hpp"
#include "mge/core/Timer.hpp"

ColorFlasher::ColorFlasher(GameObject* pOwner)
{
    addBehaviourToGO(pOwner);
}

ColorFlasher::~ColorFlasher()
{
    //dtor
}

void ColorFlasher::addBehaviourToGO(GameObject* pGameObject)
{
    pGameObject->addBehaviour(this);
}

void ColorFlasher::setMaterial(std::shared_ptr<LitTextureMaterial> pMaterial)
{
    _material = pMaterial;
}

void ColorFlasher::update(float pStep)
{
    if (_material == NULL)
        return;

    if (_flashing)
    {
        float fraction = (Timer::now() - _startedAt) / _duration;

        if (fraction >= 1.0f)
        {
            _flashing = false;
            _material->diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
            return;
        }

        _material->diffuseColor = glm::mix(_flashColor, glm::vec3(1.0f), fraction);
    }
}

void ColorFlasher::flash(glm::vec3 pFlashColor, float pDuration)
{
    _flashing = true;
    _flashColor = pFlashColor;
    _duration = pDuration;
    _startedAt = Timer::now();
}
