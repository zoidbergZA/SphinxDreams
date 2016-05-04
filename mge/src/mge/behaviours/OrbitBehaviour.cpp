#include "OrbitBehaviour.hpp"
#include <SFML/Graphics.hpp>
#include <glm.hpp>
#include "mge/core/GameObject.hpp"
#include <iostream>

OrbitBehaviour::OrbitBehaviour(GameObject* pTarget, float distance, float speed, float maxAngle, GameObject* pOwner)
    : AbstractBehaviour(), _target(pTarget), _distance(distance), _speed(speed), _maxAngle(maxAngle) {
    addBehaviourToGO(pOwner);
    _tilt = 0;
    _orbitPosition = glm::vec3(0,0,0);
    _mouseOld = glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
    _mouseDelta = glm::vec2(sf::Mouse::getPosition().x - _mouseOld.x, sf::Mouse::getPosition().y - _mouseOld.y);
}

OrbitBehaviour::~OrbitBehaviour() {
    //dtor
}

void OrbitBehaviour::addBehaviourToGO(GameObject* pGameObject) {
    pGameObject->addBehaviour(this);
}

void OrbitBehaviour::update(float step) {
    //mouse movement
    _mouseDelta = glm::vec2(sf::Mouse::getPosition().x - _mouseOld.x, sf::Mouse::getPosition().y - _mouseOld.y);
    _mouseOld = glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);


    //orbit behaviour goes here
    _theta += _mouseDelta.x * step *0.3f;
    _tilt += _mouseDelta.y * step *0.3f;
    _tilt = glm::clamp(_tilt, -_maxAngle, _maxAngle);

    _orbitPosition.x = std::cos(_theta);
    _orbitPosition.z = std::sin(_theta);
    _orbitPosition.y = std::sin(_tilt);
    _orbitPosition = glm::normalize(_orbitPosition);
    _orbitPosition *= _distance;

    //place owner transform in correct position
    _owner->setLocalPosition(_target->getWorldPosition() + _orbitPosition);

    _owner->setTransform(
        glm::inverse (
            glm::lookAt (_owner->getLocalPosition(), _target->getWorldPosition(), glm::vec3(0,1,0))
        )
    );
}
