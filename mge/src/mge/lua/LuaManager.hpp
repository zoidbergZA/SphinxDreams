#ifndef LUAMANAGER_H
#define LUAMANAGER_H

#include <iostream>

#include "mge/core/GameObject.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/behaviours/MeshRenderer.hpp"
#include "mge/materials/AbstractMaterial.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/core/World.hpp"

namespace LuaManager
{
    static void testFunction(std::string pMessage)
    {
        GameObject* go = new GameObject("lua gameObject");
        World::Instance()->add(go);
    }

    static GameObject* createProp(std::string pFilename, std::string pMaterial, std::string pName)
    {
        GameObject* go = new GameObject(pName);
        World::Instance()->add(go);

        std::shared_ptr<AbstractMaterial> mb = std::shared_ptr<AbstractMaterial>(new ColorMaterial());
        MeshRenderer* mr = new MeshRenderer(pFilename, mb);

        go->addBehaviour(mr);

        std::cout << pName << " created from lua!" << std::endl;
        return go;
    }
}
//class LuaManager
//{
//    public:
//        LuaManager();
//        virtual ~LuaManager();
//
//        static void testFunction(std::string pMessage);
//
//    protected:
//    private:
//
//};

#endif // LUAMANAGER_H
