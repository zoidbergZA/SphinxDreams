#ifndef BASELIGHT_H
#define BASELIGHT_H +

#include <string>
#include "mge/core/GameObject.hpp"
#include "mge/core/World.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Base is just a GameObject with all basic values for the basic light implementation:
 * ambientColor, ambientIntensity, directionalLightVector, directionalLightColor
 */
class BaseLight : public AbstractBehaviour
{
    public:
        BaseLight(glm::vec3 ambientColor = glm::vec3 (1,0,0), float ambientIntensity = 0.2f, glm::vec3 pConeDirection = glm::vec3 (0,-1,0),
                  float pConeAngle = 0.0f, GameObject* pOwner = nullptr);
        virtual ~BaseLight();
        //------------- GETTERS ----------------//
        glm::vec3 getAmbientColor() { return ambientColor; }
        glm::vec3 getLightPosition() { return getOwner()->getWorldPosition(); }
        glm::vec3 getConeDirection() { return coneDirection; }
        float getConeAngle() { return coneAngle; }
        float getAmbientIntensity() { return ambientIntensity; }

        //------------- SETTERS ----------------//
        void setConeDirection(glm::vec3 pValue) { coneDirection = pValue; }

        void update(float pStep);
        void addBehaviourToGO(GameObject* pGameObject);
    private:
        //values for the uniforms
        glm::vec3 ambientColor;
        float ambientIntensity;
        glm::vec3 coneDirection;
        float coneAngle;
};

#endif // BASELIGHT_H
