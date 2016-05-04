#ifndef LIGHT_H
#define LIGHT_H

#include <AbstractBehaviour.hpp>
#include <glm.hpp>

class Light : public AbstractBehaviour
{
    public:
        Light(GameObject* pOwner);
        virtual ~Light();

        virtual void update(float step);
        void addBehaviourToGO(GameObject* pGameObject);

        glm::vec3 getColor() const;
        float getIntensity() const;
        float getInnerCone() const;
        float getOuterCone() const;

        glm::vec3 _color;
        float _intensity;
        float _innerCone;
        float _outerCone;

    protected:
    private:
};

#endif // LIGHT_H
