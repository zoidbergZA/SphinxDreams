#include <glm.hpp>

#include "mge/materials/LitColorMaterial.h"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

ShaderProgram* LitColorMaterial::_shader = NULL;

GLint LitColorMaterial::_uModelMatrix = 0;
GLint LitColorMaterial::_uViewMatrix = 0;
GLint LitColorMaterial::_uPerspectiveMatrix = 0;
GLint LitColorMaterial::_light_MVP = 0;

GLint LitColorMaterial::uGlobalAmbientIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uDiffuseColorIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uLightPositionIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uConeDirectionIndex[MAX_LIGHTS_NUM];
GLint LitColorMaterial::uConeAnglesIndex[MAX_LIGHTS_NUM];

GLint LitColorMaterial::uCameraPosIndex = 0;
GLint LitColorMaterial::_aVertex = 0;
GLint LitColorMaterial::_aNormal = 0;
GLint LitColorMaterial::_aUV = 0;
GLint LitColorMaterial::lightsUniforArraySize = 0;

int LitColorMaterial::tempSize = 0;
std::vector<Texture*> LitColorMaterial::_shadowTextures;

// ---------------- SRUFF FOR SHADOW IMPLEMENTATION ------------------ //
ShaderProgram* LitColorMaterial::_shaderSS = NULL;
GLint LitColorMaterial::_light_MVP2 = 0;
GLint LitColorMaterial::_aVertex2 = 0;
GLint LitColorMaterial::_aUV2 = 0;
GLuint FBO = 0;
glm::mat4 LitColorMaterial::biasMat = { 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0 };
// ---------------- SRUFF FOR SHADOW IMPLEMENTATION ------------------ //

LitColorMaterial::LitColorMaterial(glm::vec3 pDiffuseColor, Texture * pDiffuseTexture)
{
    _diffuseColor = pDiffuseColor;
    _diffuseTexture = pDiffuseTexture;
    _lazyInitializeShader();
}

LitColorMaterial::~LitColorMaterial()
{
    //dtor
}

void LitColorMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

string LitColorMaterial::uniName(string propertyName, int lightIndex) {
    std::stringstream ss;
    ss << "pointLights[" << lightIndex << "]." << propertyName;
    std::string uniformName = ss.str();
    return uniformName;
}

void LitColorMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader)
    {
        //create _shader for lights and _shaderSS for shadows START
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"litcolor.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"litcolor.fs");
        _shader->finalize();

        _shaderSS = new ShaderProgram();
        _shaderSS->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"shadowMap.vs");
        _shaderSS->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"shadowMap.fs");
        _shaderSS->finalize();
        _light_MVP2         = _shaderSS->getUniformLocation("light_MVP");
        _aVertex2           = _shaderSS->getAttribLocation("vertex");
        _aUV2               = _shaderSS->getAttribLocation("uv");
        //create _shader for lights and _shaderSS for shadows END

        //SHADOW SHADER: cachee all the uniform and attribute indexes
        glEnable(GL_DEPTH_TEST);
        glGenFramebuffers(1, &FBO);
        for (unsigned int i = 0; i < World::Instance()->sceneLights().size(); ++i) {
            Texture* texture = Texture::load("ShadowTexture_" + std::to_string(i), true);
            _shadowTextures.push_back(texture);
        }
        glBindTexture(GL_TEXTURE_2D, _shadowTextures.at(0)->getId());
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadowTextures.at(0)->getId(), 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        int i = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if(i != GL_FRAMEBUFFER_COMPLETE) { std::cout << "Framebuffer is not OK, status=" << i << std::endl; }

        //LIGHT SHADER: cachee all the uniform and attribute indexes
        _uModelMatrix       = _shader->getUniformLocation("modelMatrix");
        _uViewMatrix        = _shader->getUniformLocation("viewMatrix");
        _uPerspectiveMatrix = _shader->getUniformLocation("perspectiveMatrix");
        _light_MVP          = _shader->getUniformLocation("light_MVP");

        uCameraPosIndex         = _shader->getUniformLocation ("cameraPos"); //eye|camera|view position
        lightsUniforArraySize   = _shader->getUniformLocation ("uniformArraySize");
        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV     = _shader->getAttribLocation("uv");

        tempSize = World::Instance()->sceneLights().size();
        if (tempSize > 0) {
            for (int i = 0; i < MAX_LIGHTS_NUM; ++i)
            {
                uGlobalAmbientIndex[i]          = _shader->getUniformLocation (uniName("globalAmbient",i));
                uDiffuseColorIndex[i]           = _shader->getUniformLocation (uniName("diffuseColor",i));
                uLightPositionIndex[i]          = _shader->getUniformLocation (uniName("lightPosition",i));
                uConeDirectionIndex[i]          = _shader->getUniformLocation (uniName("coneDirection",i));
                uConeAnglesIndex[i]             = _shader->getUniformLocation (uniName("coneAngle",i));
            }
        }
    }
}

void LitColorMaterial::render(RenderPipeline* pRenderPipeline, World* pWorld, GameObject* pGameObject, std::shared_ptr<Mesh> pMesh, Camera* pCamera)
{
    if (!_diffuseTexture) return;
    tempSize = pWorld->sceneLights().size(); //extract number of lights here
    // --------------------- SHADOW IMPLEMENTATION STARTS HERE ----------------------- //
    GameObject* tempGO = pCamera->getOwner(); // save previous owner GO to assign back to it back later
    if(tempGO != pWorld->sceneLights().at(0)->getOwner()) pCamera->setOwner(pWorld->sceneLights().at(0)->getOwner()); //'move' cam to light's position
    glm::mat4 modelMat          = pGameObject->getWorldTransform();
    glm::mat4 viewMat           = glm::inverse(pCamera->getOwner()->getWorldTransform());
    glm::mat4 perspectiveMat    = pCamera->getProjection();
    //glm::mat4 perspectiveMat    = glm::ortho(-40.0f, 40.0f, -40.0f, 40.0f, 1.0f, 7.5f);
    glm::mat4 light_MVP         = biasMat * perspectiveMat * viewMat * modelMat;

    _shaderSS->use();
    glViewport(0, 0, 1024, 1024);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUniformMatrix4fv ( _light_MVP2, 1, GL_FALSE, glm::value_ptr(light_MVP));
    glUniform1i (_shaderSS->getUniformLocation("shadowMap"), 2);
    glBindFramebuffer(GL_FRAMEBUFFER,0);
    glViewport(0, 0, 800, 600);
    pCamera->setOwner(tempGO);

    // --------------- UNCOMMENT TO RENDER SHADOW MAP ----------------//
    //glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, _shadowTextures.at(0)->getId());
    // --------------------- SHADOW IMPLEMENTATION ENDS HERE ----------------------- /*/

    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shader->use();
    //martixes used to render usual stuff
    glm::mat4 modelMatrix       = pGameObject->getWorldTransform();
    glm::mat4 viewMatrix        = glm::inverse(pCamera->getOwner()->getWorldTransform());
    glm::mat4 perspectiveMatrix = pCamera->getProjection();
    glm::vec3 cameraPos         = pCamera->getOwner()->getWorldPosition();
    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());

    glUniformMatrix4fv ( _uModelMatrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv ( _uViewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv ( _uPerspectiveMatrix, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
    glUniformMatrix4fv ( _light_MVP, 1, GL_FALSE, glm::value_ptr(light_MVP));
    glUniform3fv (uCameraPosIndex, 1, glm::value_ptr(cameraPos));
    glUniform1i (_shader->getUniformLocation("textureDiffuse"), 0);
    glUniform1i (_shader->getUniformLocation("shadowMap"), 1);

    //send current amount of lights
    glUniform1i (lightsUniforArraySize, tempSize);
    //set the material color
    if(tempSize > 0 && tempSize <= MAX_LIGHTS_NUM) {
        for (int i = 0; i < tempSize; ++i)
        {
            glUniform3fv (uGlobalAmbientIndex[i], 1,
                          glm::value_ptr(pWorld->sceneLights().at(i)->getAmbientColor() * pWorld->sceneLights().at(i)->getAmbientIntensity()));
            glUniform3fv (uDiffuseColorIndex[i], 1, glm::value_ptr(_diffuseColor));
            glUniform3fv (uLightPositionIndex[i], 1, glm::value_ptr(pWorld->sceneLights().at(i)->getLightPosition()));
            glUniform3fv (uConeDirectionIndex[i], 1, glm::value_ptr(pWorld->sceneLights().at(i)->getConeDirection()));
            glUniform1f (uConeAnglesIndex[i], pWorld->sceneLights().at(i)->getConeAngle());
        }
    }
    //now inform mesh of where to stream its data*/
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
