#ifndef MGEMARTIJN_H
#define MGEMARTIJN_H

#include <mge/core/AbstractGame.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include <lua.hpp>

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/FPS.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"

using namespace std;

class Swapper;
class GameObject;
class DebugHud;

class MGEMartijn: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MGEMartijn();
		virtual ~MGEMartijn();
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

#endif // MGEMARTIJN_H
