#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/core/GameObject.hpp"

#include <sfml/window/event.hpp>

KeysBehaviour::KeysBehaviour(float moveSpeed, float turnSpeed, GameObject* pOwner):
    AbstractBehaviour(), _moveSpeed(moveSpeed), _turnSpeed(turnSpeed) {
    addBehaviourToGO(pOwner);
}

KeysBehaviour::~KeysBehaviour() {
}

void KeysBehaviour::addBehaviourToGO(GameObject* pGameObject) {
    pGameObject->addBehaviour(this);
}

void KeysBehaviour::update( float pStep ) {
    float moveSpeed = 0.0f; //default if no keys
    float turnSpeed = 0.0f;
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up )) {
        moveSpeed = _moveSpeed;
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down )) {
        moveSpeed = -_moveSpeed;
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right )) {
        turnSpeed = -_turnSpeed;
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left )) {
        turnSpeed = +_turnSpeed;
    }
    //translate the object in its own local space
    _owner->translate( glm::vec3(0.0f, 0.0f, moveSpeed*pStep ) );

    //we can also translate directly, basically we take the z axis from the matrix
    //which is normalized and multiply it by moveSpeed*step, than we add it to the
    //translation component
    //glm::mat4 transform = _owner->getTransform();
    //transform[3] += transform[2] * moveSpeed*pStep;
    //_owner->setTransform(transform);

    //rotate the object in its own local space
    _owner->rotate( glm::radians(turnSpeed*pStep), glm::vec3(0.0f, 1.0f, 0.0f ) );
}
