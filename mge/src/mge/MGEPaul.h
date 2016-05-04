#ifndef MGEPaul_H
#define MGEPaul_H

#include <vector>
#include <string>
#include <lua.hpp>

#include <SFML/Graphics.hpp>
#include <mge/core/AbstractGame.hpp>
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
#include "mge/LuaBridge/LuaBridge.h"
#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/FPS.hpp"
#include "mge/core/Camera.hpp"
#include "mge/core/BaseLight.h"
#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobblingMaterial.h"
#include "mge/materials/LitColorMaterial.h"
#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/behaviours/OrbitBehaviourPaul.h"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/util/DebugHud.hpp"
#include "mge/config.hpp"

using namespace std;

class Swapper;
class GameObject;
class DebugHud;

class MGEPaul: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MGEPaul();
		virtual ~MGEPaul();
        virtual void initialize();

	protected:
        virtual void _initializeScene();
	    //override render to render the hud as well.
        virtual void _update();
        virtual void _processEvents();

	private:
		DebugHud* _hud;                   //hud display
        //lua_State* _lua;
        void _updateHud();
        void _initializeSceneFromLua();
};

#endif // MGEPaul_H
