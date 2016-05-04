#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <GameObject.hpp>
#include "mge/core/Camera.hpp"

class GameCamera : public GameObject
{
    public:
        GameCamera(glm::vec3 pPosition);
        virtual ~GameCamera();

        virtual void update(float pStep, const glm::mat4& pParentTransform);

    protected:
    private:
        Camera* _camera;
};

#endif // GAMECAMERA_H
