#ifndef SPHINXDREAMS_H
#define SPHINXDREAMS_H

#include <AbstractGame.hpp>
#include "mge/util/DebugHud.hpp"
#include "mge/core/FPS.hpp"

class SphinxDreams : public AbstractGame
{
    public:
        SphinxDreams();
        virtual ~SphinxDreams();
        virtual void initialize();
    protected:
        virtual void _initializeScene();
	    //override render to render the hud as well.
	    virtual void _render();
        virtual void _update();
        virtual void _processEvents();
    private:
        void _loadSceneFromLua();
        void _updateHud();
        DebugHud* _hud;
};

#endif // SPHINXDREAMS_H
