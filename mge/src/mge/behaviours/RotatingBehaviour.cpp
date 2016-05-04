#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/core/GameObject.hpp"

RotatingBehaviour::RotatingBehaviour(GameObject* pOwner):AbstractBehaviour() {
	addBehaviourToGO(pOwner);
}

RotatingBehaviour::~RotatingBehaviour() {
	//dtor
}

void RotatingBehaviour::addBehaviourToGO(GameObject* pGameObject) {
    pGameObject->addBehaviour(this);
}

void RotatingBehaviour::update( float step ) {
        _owner->rotate( step * glm::radians(30.0f), glm::vec3( 0.0f, 1.0f, 0.0f ) ); // rotates 45° per second
}
