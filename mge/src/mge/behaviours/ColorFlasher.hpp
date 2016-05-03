#ifndef COLORFLASHER_H
#define COLORFLASHER_H

#include "mge/behaviours/AbstractBehaviour.hpp"

#include "mge/materials/LitTextureMaterial.hpp"

class ColorFlasher : public AbstractBehaviour
{
    public:
        ColorFlasher(GameObject* pOwner);
        virtual ~ColorFlasher();

        virtual void update( float step );
        void addBehaviourToGO(GameObject* pGameObject);
        void setMaterial(std::shared_ptr<LitTextureMaterial> pMaterial);
        void flash(glm::vec3 pFlashColor, float pDuration);

    protected:
    private:
        bool _flashing = false;
        float _duration;
        glm::vec3 _flashColor;
        float _startedAt;
        std::shared_ptr<LitTextureMaterial> _material;
};

#endif // COLORFLASHER_H
