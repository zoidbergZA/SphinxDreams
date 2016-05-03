#include "GameCamera.hpp"
#include "mge/core/World.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"

GameCamera::GameCamera(glm::vec3 pPosition): GameObject("camera", pPosition)
{
    Camera* cb = new Camera(glm::perspective (glm::radians(80.0f), 4.0f/3.0f, 0.1f, 1000.0f), this);
//    Camera* cb = new Camera(glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 1000.0f), this);
    rotate(37.0f, glm::vec3(0,1,0));
    std::cout << "game camera created" << std::endl;
}

GameCamera::~GameCamera()
{
    //dtor
}

void GameCamera::update(float pStep, const glm::mat4& pParentTransform)
{
    GameObject::update(pStep, pParentTransform);
}
