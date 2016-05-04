#ifndef ORBITBEHAVIOUR_H
#define ORBITBEHAVIOUR_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"

class OrbitBehaviour : public AbstractBehaviour
{
    public:
        OrbitBehaviour(GameObject* pTarget, float distance, float speed, float maxAngle, GameObject* pOwner = nullptr);
        virtual ~OrbitBehaviour();

        virtual void update( float step );
        void addBehaviourToGO(GameObject* pGameObject);

    protected:

    private:
        GameObject * _target;   //what are we orbiting around and looking at?
        float _distance;        // distance from target
        float _speed;           // speed of orbit
        float _maxAngle;        // maximum tilt(x-axis) angle
        float _theta;           // circle angle
        float _tilt;             // tilt angle
        glm::vec2 _mouseOld;
        glm::vec2 _mouseDelta;
        glm::vec3 _orbitPosition; // current orbit position
};

#endif // ORBITBEHAVIOUR_H
