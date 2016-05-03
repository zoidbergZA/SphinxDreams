#include "UpdateListener.hpp"

UpdateListener::UpdateListener(LuaGame* pLuaGame) : _luaGame(pLuaGame)
{

}

UpdateListener::~UpdateListener()
{
    //dtor
}

void UpdateListener::handleFileAction(FW::WatchID watchid, const FW::String& dir, const FW::String& filename,
    FW::Action action)
{
    std::cout << "DIR (" << dir + ") FILE (" + filename + ") has event " << action << std::endl;

    //reload the hud Lua module
    _luaGame->reloadHud();
}
