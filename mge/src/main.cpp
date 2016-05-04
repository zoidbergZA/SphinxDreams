#include <iostream>

#include "mge/core/AbstractGame.hpp"
#include "mge/MGEDemo.hpp"
#include "mge/core/SphinxDreams.h"
#include "mge/MGEDemo.hpp"
#include "mge/MGEPaul.h"
#include "mge/MGEMartijn.h"
#include "mge/LuaGame.hpp"

/**
 * Main entry point for the Micro Engine.

 * Design goals:
 * - correct division of OpenGL into appropriate wrapper classes
 * - simple design
 * - each class should know as little as possible about other classes and non related parts of OpenGL
 * - the engine must allow different objects with different transforms, meshes, materials (shaders) etc
 * - consistent coding conventions
 * - reusable and extendable core set of classes which should require no modification
 *   (in other words it is possible to have a working "empty" example)
 *
 * All documentation is contained within the HEADER files, not the CPP files in possible.
 *
 */
int main()
{
    /* initialize random seed: */
    srand (time(NULL));

    std::cout << "Starting Game" << std::endl;

    AbstractGame* game = new LuaGame();
    //AbstractGame* game = new SphinxDreams();
    //AbstractGame* game = new MGEDemo();
//    AbstractGame* game = new MGEPaul();
    //AbstractGame* game = new MGEMartijn();

    game->initialize();
    game->run();

	delete game;

    return 0;
}



