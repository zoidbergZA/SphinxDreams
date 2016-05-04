#ifndef STORYWALL_H
#define STORYWALL_H

#include <GameObject.hpp>

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/LitTextureMaterial.hpp"
#include "mge/behaviours/MeshRenderer.hpp"

class StoryWall : public GameObject
{
    public:
        StoryWall(std::string pModelName, std::string pTextureName, std::string pObjectName);
        virtual ~StoryWall();

        virtual void update(float pStep, const glm::mat4& pParentTransform);
        void setTexture(string pTextureName);

    protected:
    private:
        MeshRenderer* _meshRenderer;
        std::shared_ptr<LitTextureMaterial> _material;
};

#endif // STORYWALL_H
