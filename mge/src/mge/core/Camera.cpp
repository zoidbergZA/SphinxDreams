#include <iostream>
using namespace std;

#include <glm.hpp>
#include "mge/core/Camera.hpp"
#include "mge/core/World.hpp"

Camera::Camera(glm::mat4 pProjectionMatrix, GameObject* pOwner) : AbstractBehaviour(), _projection(pProjectionMatrix)
{
    addBehaviourToGO(pOwner);
    if(World::Instance()->getMainCamera() == nullptr) World::Instance()->setMainCamera(this);
}

Camera::~Camera()
{
	//dtor
}

void Camera::addBehaviourToGO(GameObject* pGameObject)
{
    pGameObject->addBehaviour(this);
}

void Camera::update(float step)
{

}

glm::mat4& Camera::getProjection() {
    return _projection;
}

void Camera::setProjection(const glm::mat4& pProjection) {
    _projection = pProjection;
}

