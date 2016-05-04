#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <GL/glew.h>
#include <glm.hpp>
#include <AbstractBehaviour.hpp>

#include "ShaderProgram.hpp"

class ParticleSystem : public AbstractBehaviour
{
    public:
        ParticleSystem();
        virtual ~ParticleSystem();

        virtual void update(float step);
        void render();
        void addBehaviourToGO(GameObject* pGameObject);

    protected:

    private:
        ShaderProgram* _particleShader;
};

#endif // PARTICLESYSTEM_H
