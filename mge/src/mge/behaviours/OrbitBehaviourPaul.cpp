#include <glm.hpp>
#include "mge/behaviours/OrbitBehaviourPaul.h"
#include "mge/core/GameObject.hpp"
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <ctime>
#include <cmath>

OrbitBehaviourPaul::OrbitBehaviourPaul(float pDistance, float pMinXrot, float pMaxXrot, GameObject* pTarget,
                               float pMoveSpeed, float pTurnSpeed, sf::Window* pWindow, GameObject* pOwner):
AbstractBehaviour(), _distance(pDistance), _minXrot(pMinXrot), _maxXrot(pMaxXrot), _target(pTarget),
_moveSpeed(pMoveSpeed), _turnSpeed(pTurnSpeed), _myWindow(pWindow) {
    addBehaviourToGO(pOwner);
}

OrbitBehaviourPaul::~OrbitBehaviourPaul() {
    //dtor
}

void OrbitBehaviourPaul::addBehaviourToGO(GameObject* pGameObject) {
    pGameObject->addBehaviour(this);
}

void OrbitBehaviourPaul::updateCameraMovement(glm::mat4& pMatrix, bool mouse) {
    if(mouse) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) pMatrix = pMatrix * glm::translate (glm::vec3(0, 0, -_moveSpeed));
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) pMatrix = pMatrix * glm::translate (glm::vec3(0, 0, _moveSpeed));
        else if (prevX - curX > 0) pMatrix = pMatrix * glm::translate (glm::vec3(-_turnSpeed, 0, 0));
        else if (prevX - curX < 0) pMatrix = pMatrix * glm::translate (glm::vec3(_turnSpeed, 0, 0));
        else if (prevY - curY > 0) {
            if(pMatrix[2].y < _maxXrot) pMatrix = pMatrix * glm::translate (glm::vec3(0, _turnSpeed, 0));
        }
        else if (prevY - curY < 0) {
            if(pMatrix[2].y > _minXrot) pMatrix = pMatrix * glm::translate (glm::vec3(0, -_turnSpeed, 0));
        }
    } else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) pMatrix = pMatrix * glm::translate (glm::vec3(0, 0, -_moveSpeed));
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) pMatrix = pMatrix * glm::translate (glm::vec3(0, 0, _moveSpeed));
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) pMatrix = pMatrix * glm::translate (glm::vec3(-_turnSpeed, 0, 0));
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) pMatrix = pMatrix * glm::translate (glm::vec3(_turnSpeed, 0, 0));
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            if(pMatrix[2].y < 0.99f) pMatrix = pMatrix * glm::translate (glm::vec3(0, _turnSpeed, 0));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            if(pMatrix[2].y > 0.20f) pMatrix = pMatrix * glm::translate (glm::vec3(0, -_turnSpeed, 0));
        }
    }
}

void OrbitBehaviourPaul::update(float pStep) {
    prevX = (float)sf::Mouse::getPosition(*_myWindow).x;
    prevY = (float)sf::Mouse::getPosition(*_myWindow).y;

    updateCameraMovement(_owner->getTransform(), false);

    curX = (float)sf::Mouse::getPosition(*_myWindow).x;
    curY = (float)sf::Mouse::getPosition(*_myWindow).y;
    //--------------------------------------------------------------------------
    //          first way to get up, right and forward vectors
    //--------------------------------------------------------------------------
    /*glm::mat4 myTransform = _owner->getTransform();
    glm::vec3 camRight = glm::vec3(myTransform[0].x, myTransform[0].y, myTransform[0].z);
    glm::vec3 camUp = glm::vec3(myTransform[1].x, myTransform[1].y, myTransform[1].z);
    glm::vec3 camForward = glm::vec3(myTransform[2].x, myTransform[2].y, myTransform[2].z);*/

    //--------------------------------------------------------------------------
    //          second way to get up, right and forward vectors
    //--------------------------------------------------------------------------
    glm::vec3 targetPos = _target->getWorldPosition(); //target position
    glm::vec3 cameraPos = _owner->getWorldPosition(); //camera position
    glm::vec3 cameraForward = glm::normalize(cameraPos - targetPos); //camera direction
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f); //up vector - used to get camera up vector
    glm::vec3 cameraRight = glm::normalize(glm::cross(worldUp, cameraForward)); //camera right (positive) direction vector
    glm::vec3 cameraUp = glm::normalize(glm::cross (cameraForward, cameraRight)); //camera up (positive) direction vector

    _owner->setTransform(
         glm::mat4 (glm::vec4(cameraRight, 0), glm::vec4(cameraUp, 0), glm::vec4(cameraForward, 0), _owner->getTransform()[3] )
    );
}
