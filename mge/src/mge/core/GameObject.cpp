#include <cassert>
#include <iostream>
#include <stdio.h>
#include <glm.hpp>
#include <string>

#include "mge/core/Timer.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/Camera.hpp"
#include "mge/behaviours/RotatingBehaviour.hpp"

using namespace std;

GameObject::GameObject(std::string pName, glm::vec3 pPosition, bool pAddToWorld )
:	_name( pName ), _transform( glm::translate( pPosition ) ),  _parent(NULL), _children()
{
    if (pAddToWorld == true)
        World::Instance()->add(this);

    _rotateWithCamera = true;
}

GameObject::~GameObject()
{
    //detach all children
    cout << "GC running on:" << _name << endl;

    while (_children.size() > 0) {
        GameObject* child = _children[0];
        remove (child);
        delete child;
    }

    //do not forget to delete behaviour, material, mesh, collider manually if required!
//    while (_behaviours.size() > 0) {
//        AbstractBehaviour* b = _behaviours[0];
//        delete b;
//    }
}

void GameObject::setName (std::string pName)
{
    _name = pName;
}

std::string GameObject::getName() const
{
	return _name;
}

void GameObject::setActive(bool pActive)
{
    _active = pActive;
}

bool GameObject::getActive() const
{
    return _active;
}

void GameObject::setTransform (const glm::mat4& pTransform)
{
    _transform = pTransform;
}

glm::mat4& GameObject::getTransform()
{
    return _transform;
}

glm::vec3 GameObject::getForward()
{
    glm::vec4 f = _transform * glm::vec4(0,0,-1,0);
    return glm::normalize(glm::vec3(f[0],f[1],f[2]));
}

glm::vec3 GameObject::getUp()
{
    glm::vec4 f = _transform * glm::vec4(0,1,0,0);
    return glm::normalize(glm::vec3(f[0],f[1],f[2]));
}

void GameObject::pitch(float pAmount)
{
    rotate(pAmount * Timer::deltaTime(), glm::vec3(1,0,0));
}

void GameObject::roll(float pAmount)
{
    glm::vec4 axis = glm::vec4(0,0,1,0);

//    if (_rotateWithCamera)
//    {
//        glm::vec3 camZ = World::Instance()->getMainCamera()->getOwner()->getForward();
//        axis = glm::vec4(camZ, 0);
//    }

    glm::vec3 relativeAxis = glm::normalize(glm::vec3(axis[0], axis[1], axis[2]));

    rotate(pAmount * Timer::deltaTime(), relativeAxis);
}

void GameObject::yaw(float pAmount)
{
    rotate(pAmount * Timer::deltaTime(), glm::vec3(0,1,0));
}

void GameObject::setLocalPosition (glm::vec3 pPosition)
{
    _transform[3] = glm::vec4 (pPosition,1);
}

void GameObject::setLocalPositionLua (float x, float y, float z)
{
    setLocalPosition(glm::vec3(x,y,z));
}

glm::vec3 GameObject::getLocalPosition()
{
	return glm::normalize(glm::vec3(_transform[3]));
}

void GameObject::moveTo(float x, float y, float z, float pDuration)
{
    _moveStartedAt = Timer::now();
    _moveFrom = getWorldPosition();
    _moveTarget = glm::vec3(x, y, z);
    _moveDuration = pDuration;
    _moving = true;
}

void GameObject::handleMovement()
{
    if (Timer::now() >= _moveStartedAt + _moveDuration)
    {
        _moving = false;
//        std::cout << "move done pre: " << getWorldPosition() << std::endl;
        setLocalPosition(_moveTarget);
//        std::cout << "move done post: " << getWorldPosition() << std::endl;
        return;
    }
    float fraction = (Timer::now() - _moveStartedAt) / _moveDuration;
    setLocalPosition(glm::mix(_moveFrom, _moveTarget, fraction));
}

void GameObject::LookAt(GameObject* pTarget)
{
//    std::cout << getName() << " look at: " << pTarget->getName() << std::endl;
//    std::cout << pTarget->getWorldPosition() << std::endl;
//    std::cout << getWorldPosition() << std::endl;

    glm::vec3 forward = glm::normalize(GameObject::getLocalPosition() - pTarget->getLocalPosition());
    glm::vec3 right = glm::normalize(glm::cross (glm::vec3(0,1,0), forward));
    glm::vec3 up = glm::normalize(glm::cross (forward, right));

    GameObject::setTransform(
      glm::mat4 (glm::vec4(right,0), glm::vec4(up,0), glm::vec4(forward,0), glm::vec4(GameObject::getLocalPosition(),1) )
    );
}

void GameObject::WriteLogFile(const char* szString)
{
    std::cout << "writing to log file.." << std::endl;

    glm::vec3 pos = getWorldPosition();
    std::string s = getName() + " position: "
        + std::to_string(pos[0])
        + ", " + std::to_string(pos[1])
        + ", " + std::to_string(pos[2]);

//    glm::mat4 matrix = getTransform();

//    std::string s = getName() + " transform: \n"
//            + std::to_string(_transform[0][0])
//            + ", " + std::to_string(_transform[1][0])
//            + ", " + std::to_string(_transform[2][0])
//            + ", " + std::to_string(_transform[3][0])
//
//            + ", " + std::to_string(_transform[0][1])
//            + ", " + std::to_string(_transform[1][1])
//            + ", " + std::to_string(_transform[2][1])
//            + ", " + std::to_string(_transform[3][1])
//
//            + ", " + std::to_string(_transform[0][2])
//            + ", " + std::to_string(_transform[1][2])
//            + ", " + std::to_string(_transform[2][2])
//            + ", " + std::to_string(_transform[3][2])
//
//            + ", " + std::to_string(_transform[0][3])
//            + ", " + std::to_string(_transform[1][3])
//            + ", " + std::to_string(_transform[2][3])
//            + ", " + std::to_string(_transform[3][3]) + "\n";

    const char* c = s.c_str();

    FILE* pFile = fopen("logFile.txt", "a");
    fprintf(pFile, "%s\n", c);
    fclose(pFile);

    std::cout << "write completed." << std::endl;
}

//new multiple behaviours
void GameObject::addBehaviour(AbstractBehaviour* pBehaviour)
{
    pBehaviour->setOwner(this);

    if (_behaviours.count(&typeid(*pBehaviour)) == 0)
        _behaviours[&typeid(*pBehaviour)] = pBehaviour;
    else
        std::cout << "Component already exists!" << std::endl;
}

void GameObject::setParent (GameObject* pParent) {
    //remove from previous parent
    if (_parent != NULL) {
        _parent->_innerRemove(this);
        _parent = NULL;
    }

    //set new parent
    if (pParent != NULL) {
        _parent = pParent;
        _parent->_innerAdd(this);
        //pass on world to child
    }
}

GameObject* GameObject::getParent() {
    return _parent;
}

void GameObject::_innerAdd(GameObject* pChild)
{
    //set new parent
    pChild->_parent = this;
	_children.push_back(pChild);
}

void GameObject::_innerRemove (GameObject* pChild) {
    for (auto i = _children.begin(); i != _children.end(); ++i) {
        if (*i == pChild) {
            (*i)->_parent = NULL;
            _children.erase(i);
            return;
        }
    }
}

void GameObject::add (GameObject* pChild) {
    pChild->setParent(this);
}

void GameObject::remove (GameObject* pChild) {
    pChild->setParent(NULL);
}

////////////

glm::vec3 GameObject::getWorldPosition()
{
	return glm::vec3(getWorldTransform()[3]);
}

glm::mat4& GameObject::getWorldTransform()
{
    return _worldTransform;
}

////////////

void GameObject::translate(glm::vec3 pTranslation)
{
	setTransform(glm::translate(_transform, pTranslation));
}

void GameObject::move(float x, float y, float z)
{
    translate(glm::vec3(x, y, z) * Timer::deltaTime());
}

void GameObject::scale(glm::vec3 pScale)
{
	setTransform(glm::scale(_transform, pScale));
}

void GameObject::scaleLua(float x, float y, float z)
{
    setTransform(glm::scale(_transform, glm::vec3(x, y, z)));
}

void GameObject::rotate(float pAngle, glm::vec3 pAxis)
{
	setTransform(glm::rotate(_transform, pAngle, pAxis));
}

void GameObject::rotateAroundAxis(float pAngle, float x, float y, float z)
{
    rotate(pAngle * 0.017453292f, glm::vec3(x, y, z));
}

void GameObject::printStatus()
{
    std::cout << "===================================================" << std::endl;
    std::cout << "GameObject status of: " << getName() << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "position:          " << getWorldPosition() << std::endl;
    std::cout << "TODO: print scale" << std::endl;
    std::cout << "forward direction: " << getForward() << std::endl;
    std::cout << "up direction:      " << getUp() << std::endl;
    std::cout << "transform:" << std::endl << getTransform() << std::endl;
    std::cout << std::endl;

    WriteLogFile("status log for gameObject");
}

void GameObject::update(float pStep, const glm::mat4& pParentTransform)
{
    if (!_active)
        return;

    _worldTransform = pParentTransform * _transform;

    for (auto const& value: _behaviours)
    {
        if (value.second->enabled == true)
            value.second->update(pStep);
    }

    for (int i = _children.size()-1; i >= 0; --i ) {
        _children[i]->update(pStep, _worldTransform);
    }

    if (_moving)
        handleMovement();
}

int GameObject::getChildCount() {
    return _children.size();
}

GameObject* GameObject::getChildAt(int pIndex) {
    return _children[pIndex];
}

