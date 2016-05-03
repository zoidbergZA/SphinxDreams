#include "mge/core/LuaLevelManger.h"
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include "mge/core/Timer.hpp"

std::vector<std::string> LuaLevelManager::objects;
std::vector<int> LuaLevelManager::positions;
std::vector<int> LuaLevelManager::rotations;
std::vector<int> LuaLevelManager::scalings;
std::vector<std::string> LuaLevelManager::textures;
std::vector<std::string> LuaLevelManager::materials;
std::vector<GameObject*> LuaLevelManager::_gameObjects;
std::vector<int> LuaLevelManager::cameraDetails;
std::vector<int> LuaLevelManager::current_position = { 6, 6, 6 };
bool LuaLevelManager::sendKeyPressedToLua = false;
bool LuaLevelManager::sendKeyReleasedToLua = false;
float LuaLevelManager::gameTime = 0.0f;
float LuaLevelManager::lastDistanceCheckedAt = 0.0f;
float LuaLevelManager::coolDown = 2.0f;
lua_State* LuaLevelManager::_lua = luaL_newstate();

LuaLevelManager::LuaLevelManager()
{
    lastDistanceCheckedAt = Timer::now();
}

LuaLevelManager::~LuaLevelManager()
{
    //dtor
}

//add here all C++ functions that need to be registered in Lua
void LuaLevelManager::registerFunctionsInLua()
{
    lua_register(_lua, "Create", Create);
    lua_register(_lua, "getObjectPositionLua", getObjectPositionLua);
    lua_register(_lua, "moveObject", moveObject);
}

void LuaLevelManager::LoadLevel(World* _world)
{
    registerFunctionsInLua();
    fillInArrays(_lua);

}

std::vector<GameObject*> LuaLevelManager::makeObjectsForLevel()
{
    fillInArrays(_lua);
    registerFunctionsInLua();
    std::vector<GameObject*> gameObjects;

    for (int i = 0; i < objects.size(); ++i)
    {
        //---------------- DEFINE COLORS IN CASE OF COLOR MATERIAL -----------------//
        glm::vec3 tempColor = glm::vec3(1,0,0);
        if(materials[i] == "red") tempColor = glm::vec3(1,0,0);
        if(materials[i] == "green") tempColor = glm::vec3(0,1,0);
        if(materials[i] == "blue") tempColor = glm::vec3(0,0,1);
        if(materials[i] == "white") tempColor = glm::vec3(1,1,1);
        if(materials[i] == "black") tempColor = glm::vec3(0,0,0);
        if(materials[i] == "yellow") tempColor = glm::vec3(1,1,0);
        //---------------- DEFINE COLORS IN CASE OF COLOR MATERIAL -----------------//

        //---------------- CREATE OBJECTS FROM GIVEN LUA DATA -----------------//
        if(objects[i] == "teapot")
        {
//            Mesh* mesh = Mesh::load (config::MGE_MODEL_PATH+textures[i]+".obj");
//            AbstractMaterial* material = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+materials[i]+".jpg"));
//            GameObject* teapot = new GameObject ("teapot", glm::vec3(positions[i*3],positions[i*3+1],positions[i*3+2]));
//            teapot->setMesh (mesh);
//            teapot->rotate(rotations[i*4], glm::vec3(rotations[i*4+1],rotations[i*4+2],rotations[i*4+3]));
//            teapot->setMaterial(material);
//            teapot->setBehaviour (new KeysBehaviour());
//            gameObjects.push_back(teapot);
        } else if(objects[i] == "monkey")
        {
//            Mesh* mesh = Mesh::load (config::MGE_MODEL_PATH+textures[i]+".obj");
//            AbstractMaterial* material = new ColorMaterial (tempColor);
//            GameObject* monkey = new GameObject ("monkey", glm::vec3(positions[i*3],positions[i*3+1],positions[i*3+2]));
//            monkey->rotate(rotations[i*4], glm::vec3(rotations[i*4+1],rotations[i*4+2],rotations[i*4+3]));
//            monkey->setMesh (mesh);
//            monkey->setMaterial(material);
////            monkey->setBehaviour (new RotatingBehaviour());
//            gameObjects.push_back(monkey);
        } else if(objects[i] == "car")
        {
//            Mesh* mesh = Mesh::load (config::MGE_MODEL_PATH+textures[i]+".obj");
//            AbstractMaterial* material = new ColorMaterial (tempColor);
//            GameObject* car = new GameObject ("car", glm::vec3(positions[i*3],positions[i*3+1],positions[i*3+2]));
//            car->rotate(rotations[i*4], glm::vec3(rotations[i*4+1],rotations[i*4+2],rotations[i*4+3]));
//            car->setMesh (mesh);
//            car->setMaterial(material);
//            gameObjects.push_back(car);
        } else if(objects[i] == "plane")
        {
//            Mesh* mesh = Mesh::load (config::MGE_MODEL_PATH+textures[i]+".obj");
//            AbstractMaterial* material = new TextureMaterial (Texture::load (config::MGE_TEXTURE_PATH+materials[i]+".jpg"));
//            GameObject* plane = new GameObject ("plane", glm::vec3(positions[i*3],positions[i*3+1],positions[i*3+2]));
//            plane->scale(glm::vec3(scalings[i], scalings[i], scalings[i]));
//            plane->setMesh (mesh);
//            plane->setMaterial(material);
//            gameObjects.push_back(plane);
        }
    }
    _gameObjects = gameObjects;
    return gameObjects;
}

void LuaLevelManager::detectCollision(lua_State* _lua)
{
    for (int i = 0; i < _gameObjects.size()-1; ++i)
    {
        for (int j = i+1; j < _gameObjects.size(); ++j)
        {
            glm::vec3 obj1 = _gameObjects.at(i)->getWorldPosition();
            glm::vec3 obj2 = _gameObjects.at(j)->getWorldPosition();
            float d = glm::distance(obj1, obj2);
            if(d <= 1.0f && _gameObjects.at(i)->getName() != "plane" && _gameObjects.at(j)->getName() != "plane"
               && Timer::now() - lastDistanceCheckedAt > coolDown)
            {
                std::cout << "collision between " << _gameObjects.at(i)->getName() << " and " << _gameObjects.at(j)->getName() << std::endl;
                std::cout << "distance: " << d << " between " << _gameObjects.at(i)->getName() << " and " << _gameObjects.at(j)->getName() << std::endl;
                lastDistanceCheckedAt = Timer::now();
                //-------------------- SEND ALL THIS TO LUA --------------------//
                luaL_loadfile(_lua, "level.lua");
                lua_pushinteger(_lua, i);
                lua_setglobal(_lua, "collider_1");
                lua_pushinteger(_lua, j);
                lua_setglobal(_lua, "collider_2");
            }
        }
    }
}

void LuaLevelManager::luaUpdateLoop(lua_State* _lua)
{
    luaL_loadfile(_lua, "level.lua");
    lua_getglobal(_lua, "Update");
    lua_call(_lua, 0, 0);
}

//------------- FUNCTION CALLED FROM LUA WITHIN UPDATE LOOP -----------------//
int LuaLevelManager::moveObject(lua_State* _lua)
{
    // get id from argument
	int obj_id = lua_tonumber(_lua, 1);
    _gameObjects.at(obj_id)->translate(glm::vec3(0, 0, 0.05f));
    _gameObjects.at(obj_id)->rotate( glm::radians(1.5f), glm::vec3(0.0f, 0.0f, 1.0f ) );
	// return the number of results
    return 1;
}
//------------- FUNCTION CALLED FROM LUA WITHIN UPDATE LOOP -----------------//

int LuaLevelManager::Create(lua_State* _lua)
{
    // get id from argument
	int obj_type = lua_tonumber(_lua, 1);
	std::cout << "ID ========>>>>> " << obj_type << std::endl;
//    glm::vec3 obj_pos;
//    obj_pos.x = lua_tonumber(_lua, 2);
//    obj_pos.y = lua_tonumber(_lua, 3);
//    obj_pos.z = lua_tonumber(_lua, 4);
//    std::cout << obj_type << " | " << obj_pos.x << " | " << obj_pos.y << " | " << obj_pos.z << std::endl;

	// return the number of results
    return 1;
}

//Camera* LuaLevelManager::_camera()
//{
//    Camera* camera = new Camera ("camera", glm::vec3(cameraDetails[0],cameraDetails[1],cameraDetails[2]));
//    camera->rotate(glm::radians((float)cameraDetails[5]), glm::vec3(cameraDetails[5],cameraDetails[6],cameraDetails[7]));
//    return camera;
//}

void LuaLevelManager::fillInArrays(lua_State* _lua)
{
    luaL_openlibs(_lua);
    luaL_loadfile(_lua, "level.lua");
    lua_call(_lua, 0, 0);
    //--------------- OBJECTS ------------------//
    lua_getglobal(_lua, "objects");
    if(lua_isnil(_lua, -1) == true)
    {
        cout << "Objects array in lua is empty" << endl;
    } else {
        lua_pushnil(_lua);
        while(lua_next(_lua, -2)) {
            LuaLevelManager::objects.push_back((std::string)lua_tostring(_lua, -1));
            lua_pop(_lua, 1);
        }
    }

    //--------------- POSITIONS ------------------//
    lua_getglobal(_lua, "positions");
    if(lua_isnil(_lua, -1) == true)
    {
        cout << "Positions array in lua is empty" << endl;
    } else {
        lua_pushnil(_lua);
        while(lua_next(_lua, -2)) {
            LuaLevelManager::positions.push_back((int)lua_tonumber(_lua, -1));
            lua_pop(_lua, 1);
        }
    }

    //--------------- ROTATIONS ------------------//
    lua_getglobal(_lua, "rotations");
    if(lua_isnil(_lua, -1) == true)
    {
        cout << "Rotations array in lua is empty" << endl;
    } else {
        lua_pushnil(_lua);
        while(lua_next(_lua, -2)) {
            LuaLevelManager::rotations.push_back((int)lua_tonumber(_lua, -1));
            lua_pop(_lua, 1);
        }
    }

    //--------------- SCALINGS ------------------//
    lua_getglobal(_lua, "scalings");
    if(lua_isnil(_lua, -1) == true)
    {
        cout << "Scalings array in lua is empty" << endl;
    } else {
        lua_pushnil(_lua);
        while(lua_next(_lua, -2)) {
            LuaLevelManager::scalings.push_back((int)lua_tonumber(_lua, -1));
            lua_pop(_lua, 1);
        }
    }

    //--------------- TEXTURES ------------------//
    lua_getglobal(_lua, "textures");
    if(lua_isnil(_lua, -1) == true)
    {
        cout << "Textures array in lua is empty" << endl;
    } else {
        lua_pushnil(_lua);
        while(lua_next(_lua, -2)) {
            LuaLevelManager::textures.push_back((std::string)lua_tostring(_lua, -1));
            lua_pop(_lua, 1);
        }
    }

    //--------------- MATERIALS ------------------//
    lua_getglobal(_lua, "materials");
    if(lua_isnil(_lua, -1) == true)
    {
        cout << "Materials array in lua is empty" << endl;
    } else {
        lua_pushnil(_lua);
        while(lua_next(_lua, -2)) {
            LuaLevelManager::materials.push_back((std::string)lua_tostring(_lua, -1));
            lua_pop(_lua, 1);
        }
    }

    //--------------- Camera ------------------//
    lua_getglobal(_lua, "camera");
    if(lua_isnil(_lua, -1) == true)
    {
        cout << "Camera array in lua is empty" << endl;
    } else {
        lua_pushnil(_lua);
        while(lua_next(_lua, -2)) {
            LuaLevelManager::cameraDetails.push_back((int)lua_tonumber(_lua, -1));
            lua_pop(_lua, 1);
        }
    }
}

void LuaLevelManager::getKeyActions(lua_State* _lua, bool pressed)
{
    luaL_loadfile(_lua, "level.lua");
    if (pressed == true) {
        lua_pushinteger(_lua, 1);
        lua_setglobal(_lua, "keyIsPressed");
        lua_pushinteger(_lua, 0);
        lua_setglobal(_lua, "keyIsReleased");
    } else {
        lua_pushinteger(_lua, 1);
        lua_setglobal(_lua, "keyIsReleased");
        lua_pushinteger(_lua, 0);
        lua_setglobal(_lua, "keyIsPressed");
    }
    (pressed == true) ? sendKeyPressedToLua = false : sendKeyReleasedToLua = false;
    //--- HERE WE ARE CALLING LUA FUNCTION TO DEMONSTRATE AVAILABILITY OF ---
    //--- KEY PRESSED/RELEASED, GAME TIME, GO POSITIONS FROM WITHIN LUA SCRIPT UPON REQUEST ---
    lua_getglobal(_lua, "test");
    lua_call(_lua, 0, 0);
}

void LuaLevelManager::setGameTimeToLua(lua_State* _lua)
{
    gameTime = Timer::now();
    luaL_loadfile(_lua, "level.lua");
    lua_pushinteger(_lua, (int)gameTime);
    lua_setglobal(_lua, "gameTime");
}

void LuaLevelManager::getObjectPositionCPP(int id)
{
    current_position.clear();
    current_position.push_back(_gameObjects.at(id)->getWorldPosition().x);
    current_position.push_back(_gameObjects.at(id)->getWorldPosition().y);
    current_position.push_back(_gameObjects.at(id)->getWorldPosition().z);
}

//--------------- FUNCTION THAT GETS CURRENT OBJECT POSITION BASED ON ID ------------------//
int LuaLevelManager::getObjectPositionLua(lua_State* _lua)
{
    // get id from argumet
	int id = lua_tonumber(_lua, 1);
    // update current position of the needed object
    getObjectPositionCPP(id);
    // push everything we have
    lua_pushnumber(_lua, current_position.at(0));
	lua_pushnumber(_lua, current_position.at(1));
    lua_pushnumber(_lua, current_position.at(2));
	// return the number of results
    return 3;
}
//--------------- FUNCTION THAT GETS CURRENT OBJECT POSITION BASED ON ID ------------------//






























