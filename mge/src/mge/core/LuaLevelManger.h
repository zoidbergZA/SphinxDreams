#ifndef LUALEVELMANAGER_H
#define LUALEVELMANAGER_H
#include <glm.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"
#include "mge/core/FPS.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
#include "mge/core/AbstractGame.hpp"
#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"

#include "mge/util/DebugHud.hpp"

#include <lua.hpp>
#include <mge/config.hpp>

class LuaLevelManager
{
    public:
        LuaLevelManager();
        virtual ~LuaLevelManager();
        static void fillInArrays(lua_State* _lua);
        static void getKeyActions(lua_State* _lua, bool pressed);
        static void setGameTimeToLua(lua_State* _lua);
        static void getObjectPositionCPP(int id);
        static void detectCollision(lua_State* _lua);
        static void luaUpdateLoop(lua_State* _lua);
        static void LoadLevel(World* _world);
        static void registerFunctionsInLua();

        static int moveObject(lua_State* _lua);
        static int getObjectPositionLua(lua_State* _lua);
        static int Create(lua_State* _lua);

        static std::vector<std::string> objects;
        static std::vector<int> positions;
        static std::vector<int> rotations;
        static std::vector<int> scalings;
        static std::vector<std::string> textures;
        static std::vector<std::string> materials;
        static std::vector<int> cameraDetails;
        static std::vector<int> current_position;
        static std::vector<GameObject*> makeObjectsForLevel();
        static std::vector<GameObject*> _gameObjects;
        static Camera* _camera();
        static bool sendKeyPressedToLua;
        static bool sendKeyReleasedToLua;
        static float gameTime;
        static lua_State * _lua;

    protected:
    private:
        static float lastDistanceCheckedAt;
        static float coolDown;
};

#endif // LUALEVELMANAGER_H
