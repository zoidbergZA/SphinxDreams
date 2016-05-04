#include <iostream>
#include <GL/glew.h>

#include "config.hpp"
#include "RenderPipeline.hpp"
#include "World.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "Camera.hpp"
#include "LuaGame.hpp"

RenderPipeline::RenderPipeline()
{
    //    //setup openGL settings
	std::cout << "Initializing render settings..." << std::endl;

    glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE ); // default GL_BACK
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glClearColor((float)0x2d/0xff, (float)0x6b/0xff, (float)0xce/0xff, 1.0f );
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    std::cout << "Render settings loaded." << std::endl << std::endl;

    initializeParticleSystem();
    initializeDepthmap();
//    calculateLightSpaceMatrix();
}

RenderPipeline::~RenderPipeline()
{
    glDeleteFramebuffers(1, &_depthMapFBO);
}

GLuint RenderPipeline::getShadowMap()
{
    return _depthMap;
}

void RenderPipeline::initializeParticleSystem()
{
    std::cout << "initializing particle system..." << std::endl;

    _particlesGameObject = new GameObject("particles GameObject", glm::vec3(0.0f), true);
    _particleSystem = new ParticleSystem();
    _particleSystem->addBehaviourToGO(_particlesGameObject);
}

void RenderPipeline::calculateLightSpaceMatrix()
{
    //light space transform
    GLfloat near_plane = 1.0f, far_plane = 60.0f;
//    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightProjection = glm::perspective (glm::radians(60.0f), 4.0f/3.0f, near_plane, far_plane);
//    glm::mat4 lightView = glm::lookAt(glm::vec3(-4, 3, 10), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 lightPos = LuaGame::mainLight->getWorldPosition();
    glm::vec3 lightForward = LuaGame::mainLight->getForward();
    glm::mat4 lightView = glm::lookAt(
          lightPos,                     // from
          lightPos + lightForward,      // target
          glm::vec3(0.0f, 1.0f, 0.0f)   // up
    );

    lightSpaceMatrix = lightProjection * lightView;
}

void RenderPipeline::initializeDepthmap()
{
    //create depthmap shader programs
    _depthPreview = new ShaderProgram();
    _depthPreview->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"shadowMap.vs");
    _depthPreview->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"shadowMap.fs");
    _depthPreview->finalize();

    //create a framebuffer object for rendering the depth map
    glGenFramebuffers(1, &_depthMapFBO);
    glGenTextures(1, &_depthMap);
    glBindTexture(GL_TEXTURE_2D, _depthMap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                 SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    _depthMapperMaterial = std::shared_ptr<AbstractMaterial>(new DepthMapper(_depthMapFBO, _depthMap, SHADOW_WIDTH, SHADOW_HEIGHT));
}

void RenderPipeline::render (World* pWorld)
{
    calculateLightSpaceMatrix();

    //render world to depth map
    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);
    render (pWorld, pWorld, pWorld->getMainCamera(), true, true);
    glCullFace(GL_BACK);

    //show shadowMap (testing only)
//    showShadowMap();

    //render world normally
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render (pWorld, pWorld, pWorld->getMainCamera(), true, false);

    World::Instance()->renderDebugInfo();
}

void RenderPipeline::render (World* pWorld, GameObject * pGameObject, Camera * pCamera, bool pRecursive, bool pShadowMap)
{
    if (!pGameObject->getActive())
        return;

    MeshRenderer* meshRenderer = pGameObject->getBehaviour<MeshRenderer>();

    if (meshRenderer != NULL)
    {
        if (pShadowMap)
            meshRenderer->render(this, _depthMapperMaterial);
        else
            meshRenderer->render(this);
    }

    if (!pRecursive) return;

    int childCount = pGameObject->getChildCount();
    if (childCount < 1) return;

    //note that with a loop like this, deleting children during rendering is not a good idea :)
    for (int i = 0; i < childCount; i++) {
        render (pWorld, pGameObject->getChildAt(i), pCamera, pRecursive, pShadowMap);
    }
}

void RenderPipeline::showShadowMap()
{
    // --- depth map preview quad ---

    GLfloat quadVertices[] = {   // Vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // Positions   // TexCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    // Setup screen VAO
    GLuint quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glBindVertexArray(0);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set clear color to white (not really necessery actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST); // We don't care about depth information when rendering a single quad

    // Draw Screen
    _depthPreview->use();
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, _depthMap);	// Use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);
}
