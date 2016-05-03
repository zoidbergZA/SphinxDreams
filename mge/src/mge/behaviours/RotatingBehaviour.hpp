#ifndef ROTATINGBEHAVIOUR_H
#define ROTATINGBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * Simply rotates the object around its origin
 */
class RotatingBehaviour : public AbstractBehaviour
{
	public:
		RotatingBehaviour(GameObject* pOwner = nullptr);
		virtual ~RotatingBehaviour();

		virtual void update( float step );
		void addBehaviourToGO(GameObject* pGameObject);

};

#endif // ROTATINGBEHAVIOUR_H
