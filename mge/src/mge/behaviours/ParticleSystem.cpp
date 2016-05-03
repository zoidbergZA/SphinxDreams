#include <algorithm>

#include "ParticleSystem.hpp"
#include "GameObject.hpp"
#include "config.hpp"

ParticleSystem::ParticleSystem()
{
    //create shader program
    _particleShader = new ShaderProgram();
    _particleShader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"particleShader.vs");
    _particleShader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"particleShader.fs");
    _particleShader->finalize();
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::update(float step)
{

}

void ParticleSystem::render()
{

}

void ParticleSystem::addBehaviourToGO(GameObject* pGameObject)
{
    pGameObject->addBehaviour(this);
}
