#include "WobblingMaterial.h"
#include <glm.hpp>

#include "mge/materials/WobblingMaterial.h"
#include "mge/config.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/Mesh.hpp"
#include <iostream>
#include <ctime>
#include <cmath>

ShaderProgram* WobblingMaterial::_shader = NULL;

GLint WobblingMaterial::_uMVPMatrix = 0;
GLint WobblingMaterial::_uDiffuseColor = 0;

GLint WobblingMaterial::_aVertex = 0;
GLint WobblingMaterial::_aNormal = 0;
GLint WobblingMaterial::_aUV = 0;
GLint WobblingMaterial::_offsetIndex = 0;
GLint WobblingMaterial::_timeIndex = 0;
GLfloat WobblingMaterial::offset[] = {0,0};
GLfloat WobblingMaterial::_time[] = {0,0};

WobblingMaterial::WobblingMaterial(glm::vec3 pDiffuseColor):_diffuseColor (pDiffuseColor)
{
    //every time we create an instance of colormaterial we check if the corresponding shader has already been loaded
    _lazyInitializeShader();
}

void WobblingMaterial::_lazyInitializeShader() {
    //this shader contains everything the material can do (it can render something in 3d using a single color)
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"wobble.vs");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"wobble.fs");
        _shader->finalize();
        offset[0] = (0.25f * -cos (clock()/500.0f));
        offset[1] = (0.25f * cos (clock()/500.0f));
        //cache all the uniform and attribute indexes
        _uMVPMatrix=  _shader->getUniformLocation("mvpMatrix");
        _uDiffuseColor =    _shader->getUniformLocation("diffuseColor");
        _offsetIndex = _shader->getUniformLocation("offset");
        _timeIndex = _shader->getUniformLocation("_time");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

WobblingMaterial::~WobblingMaterial()
{
    //dtor
}

void WobblingMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void WobblingMaterial::render(World* pWorld, GameObject* pGameObject, std::shared_ptr<Mesh> pMesh, Camera* pCamera) {
    _shader->use();
    _time[0] = clock();
    _time[1] = clock();
    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pCamera->getProjection() * glm::inverse(pCamera->getOwner()->getWorldTransform()) * pGameObject->getWorldTransform();
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //set the material color
    glUniform3fv (_uDiffuseColor, 1, glm::value_ptr(_diffuseColor));
    glUniform2fv (_offsetIndex, 1, offset);
    glUniform2fv (_timeIndex, 1, _time);
    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
