#ifndef OrbitBehaviourPaul_H
#define OrbitBehaviourPaul_H

#include <glm.hpp>
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/core/GameObject.hpp"
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

/**
 * Orbits around target left-/right-/for-/backwards
 */
class OrbitBehaviourPaul : public AbstractBehaviour
{
    public:
        OrbitBehaviourPaul(float pDistance, float pMinXrot, float pMaxXrot, GameObject* pTarget,
                       float moveSpeed, float turnSpeed, sf::Window* pWindow, GameObject* pOwner = nullptr);
        virtual ~OrbitBehaviourPaul();

        virtual void update( float pStep );
        void addBehaviourToGO(GameObject* pGameObject);
        sf::Event event;
        float prevX;
        float prevY;
        float curX;
        float curY;

    private:
        float _distance;
        float _minXrot;
        float _maxXrot;
        GameObject * _target;
        float _moveSpeed;
        float _turnSpeed;

        sf::Window* _myWindow;
        void updateCameraMovement( glm::mat4& pMatrix, bool mouse );

};

#endif // OrbitBehaviourPaul_H
