#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "mge/core/GameObject.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * The camera's own transform is used to generate a world to view matrix by taking the inverse of the camera transform.
 */
class Camera : public AbstractBehaviour
{
	public:
		Camera(glm::mat4 pProjectionMatrix = glm::perspective (glm::radians(60.0f), 4.0f/3.0f, 0.1f, 1000.0f), GameObject* pOwner = nullptr);
		virtual ~Camera();

        virtual void update(float pStep);
        void addBehaviourToGO(GameObject* pGameObject);
        glm::mat4& getProjection();
        void setProjection(const glm::mat4& pProjection);

	private:
		glm::mat4 _projection;

};

#endif // CAMERA_H
