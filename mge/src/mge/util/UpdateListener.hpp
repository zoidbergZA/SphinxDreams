#ifndef UPDATELISTENER_H
#define UPDATELISTENER_H

#include <FileWatcher/FileWatcher.h>

#include "mge/LuaGame.hpp"

class UpdateListener : public FW::FileWatchListener
{
    public:
        UpdateListener(LuaGame* pLuaGame);
        virtual ~UpdateListener();

        void handleFileAction(FW::WatchID watchid, const FW::String& dir, const FW::String& filename,
		FW::Action action);
    protected:
        LuaGame* _luaGame;

    private:
};

#endif // UPDATELISTENER_H
