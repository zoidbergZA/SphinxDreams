#ifndef RENDERPIPELINE_H
#define RENDERPIPELINE_H

class World;
class GameObject;
class Camera;

#include "mge/materials/DepthMapper.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/core/ShaderProgram.hpp"
#include "mge/core/RenderPipeline.hpp"
#include "ParticleSystem.hpp"

class RenderPipeline
{
    public:
        RenderPipeline();
        virtual ~RenderPipeline();

        //render whole world
        void render (World* pWorld);

        //render specific game object within the world (using world's light settings etc)
        void render (World* pWorld, GameObject* pGameObject, Camera* pCamera, bool pRecursive, bool pShadowMap);

        GLuint getShadowMap();

        glm::mat4 lightSpaceMatrix;
    protected:

    private:
        void initializeParticleSystem();
        void calculateLightSpaceMatrix();
        void initializeDepthmap();
        void showShadowMap();

        const GLuint SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;
        std::shared_ptr<AbstractMaterial> _depthMapperMaterial;
        ShaderProgram* _depthPreview;
        GLuint _depthMapFBO;
        GLuint _depthMap;

        // particle system
        GameObject* _particlesGameObject;
        ParticleSystem* _particleSystem;
};

#endif // RENDERPIPELINE_H
