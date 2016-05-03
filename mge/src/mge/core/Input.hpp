#ifndef INPUT_H
#define INPUT_H

#include "mge/core/AbstractGame.hpp"

class Input
{
    public:
        Input();
        virtual ~Input();

        static bool _keyDown[256]; // make private/protected
        static bool getKeyDown(int pKeycode);
        static bool getKey(int pKeycode);

    protected:

    private:
};
#endif // INPUT_H
