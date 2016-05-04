#ifndef LITTEXTUREMATERIAL_H
#define LITTEXTUREMATERIAL_H

#include "mge/core/Texture.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/AbstractMaterial.hpp"

class LitTextureMaterial : public AbstractMaterial
{
    public:
        LitTextureMaterial (Texture* pDiffuseTexture);
        virtual ~LitTextureMaterial ();
        virtual void render(RenderPipeline* pRenderPipe, World* pWorld, GameObject* pGameObject, std::shared_ptr<Mesh> pMesh, Camera* pCamera);

        void setDiffuseTexture (Texture* pDiffuseTexture);
        void changeDiffuseTexture (std::string pFilename);

        glm::vec3 diffuseColor;

    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        Texture* _diffuseTexture;
};

#endif // LITTEXTUREMATERIAL_H
