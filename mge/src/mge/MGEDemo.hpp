#ifndef MGEDEMO_H
#define MGEDEMO_H

#include <mge/core/AbstractGame.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <lua.hpp>

#include "mge/core/ModelViewer.hpp"
#include "mge/lua/LuaManager.hpp"
#include "mge/core/BaseHud.hpp"
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
#include "mge/MGEDemo.hpp"

using namespace std;

class Swapper;
class GameObject;
class DebugHud;

class MGEDemo: public AbstractGame
{
    //PUBLIC FUNCTIONS

	public:
		MGEDemo();
		virtual ~MGEDemo();
        virtual void initialize();
        GameObject* loadGameObject(lua_State* L, char* type);
        //void testFunc();

	protected:
        virtual void _initializeScene();
	    //override render to render the hud as well.
        virtual void _update();
        virtual void _processEvents();

	private:
//		DebugHud* _hud;                   //hud display
        BaseHud* _hud;
        void _updateHud();
        void _loadLuaScene(lua_State* L);
        static void testFunc(int i);

//        lua_State* _L;
        ModelViewer* _modelViewer;
};

#endif // MGEDEMO_H
