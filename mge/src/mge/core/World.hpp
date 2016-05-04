#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "mge/core/GameObject.hpp"

class Camera;
class BaseLight;

class World : public GameObject
{
	public:
        static World* Instance();
		void setMainCamera (Camera* pCamera);
		Camera* getMainCamera();

        void renderDebugInfo();
        void addLight(BaseLight* light);
        std::vector<BaseLight*> sceneLights() { return _lights; }

        glm::vec3 ambient;

	private:
	    World();
	    World(World const&){};             // copy constructor is private
        World& operator=(World const&){};  // assignment operator is private

        static World* _instance;

	    Camera* _mainCamera;
	    std::vector<BaseLight*> _lights; //old
};


#endif // WORLD_H
