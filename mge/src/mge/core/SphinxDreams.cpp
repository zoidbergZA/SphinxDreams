#include "SphinxDreams.h"

SphinxDreams::SphinxDreams()
{
    //ctor
}

SphinxDreams::~SphinxDreams()
{
    //dtor
}

void SphinxDreams::initialize()
{
    //setup the core part
    AbstractGame::initialize();
    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

void SphinxDreams::_initializeScene()
{
//    _renderer->setClearColor(0,0,0);
//    _loadSceneFromLua();
}

void SphinxDreams::_loadSceneFromLua()
{
    //todo: load scene from lua file here
}

void SphinxDreams::_render()
{
//    AbstractGame::_render();
    _updateHud();
}

void SphinxDreams::_update()
{
    AbstractGame::_update();
}

void SphinxDreams::_processEvents()
{
    AbstractGame::_processEvents();
}

void SphinxDreams::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string(FPS::getFPS())+"\n";
    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}
