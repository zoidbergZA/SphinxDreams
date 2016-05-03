#ifndef MAINLIGHT_H
#define MAINLIGHT_H

#include <GameObject.hpp>

#include "Light.hpp"

class MainLight : public GameObject
{
    public:
        MainLight(std::string pObjectName, glm::vec3 pPosition);
        virtual ~MainLight();

        virtual void update(float pStep, const glm::mat4& pParentTransform);

        float getIntensity() const;
        void setIntensity(float pIntensity);

        float getInnerCone() const;
        void setInnerCone(float pAngle);

        float getOuterCone() const;
        void setOuterCone(float pAngle);

        void setColor(float r, float g, float b);

        Light* light;
    protected:
    private:
};

#endif // MAINLIGHT_H
