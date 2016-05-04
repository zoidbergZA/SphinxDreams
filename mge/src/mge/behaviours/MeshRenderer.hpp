#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "mge/materials/AbstractMaterial.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/World.hpp"
#include "mge/core/RenderPipeline.hpp"

class Mesh;

class MeshRenderer : public AbstractBehaviour
{
    public:
        MeshRenderer(std::string pFilename, std::shared_ptr<AbstractMaterial> pMaterial, GameObject* pOwner = nullptr);
        virtual ~MeshRenderer();
        virtual void update( float step );
        void render(RenderPipeline* pRenderPipeline);
        void render(RenderPipeline* pRenderPipeline, std::shared_ptr<AbstractMaterial> pMaterial);
        void addBehaviourToGO(GameObject* pGameObject);

        void setMesh(std:: string pFilename);
        void setMesh(std::shared_ptr<Mesh> pMesh);
		std::shared_ptr<Mesh> getMesh() const;

		void setMaterial (std::shared_ptr<AbstractMaterial> pMaterial);
		std::shared_ptr<AbstractMaterial> getMaterial() const;

    protected:
        std::shared_ptr<Mesh> _mesh;
        std::shared_ptr<AbstractMaterial> _material;

    private:
};

#endif // MESHRENDERER_H
