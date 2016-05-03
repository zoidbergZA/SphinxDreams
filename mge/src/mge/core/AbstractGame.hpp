#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <string>

#include "mge/core/World.hpp"
#include "mge/core/RenderPipeline.hpp"

#define WINDOW_MODE sf::Style::Fullscreen // Default, Fullscreen --NOTE: Use native resolution for fullscreen!
#define SCREEN_WIDTH 1920 // 1920,  1366,   1600,   1680,   1920
#define SCREEN_HEIGHT 1080 //  1080,   768,    900,   1050,   1080
#define MSAA 8
#define RENDERDEBUG false

using namespace std;

//class World;
//class Renderer;

/**
 * Defines the basic structure for a game, with defaults already filled in.
 * Your main game loop should run:
 *
 *  initialize
 *  run
 *
 * in order.
 */
class AbstractGame
{
    public:

        AbstractGame();
        virtual ~AbstractGame();

        //creates a window, initializes glew, a renderer and a world instance
        virtual void initialize();
        //run the actual process of updating all objects, rendering them and processing events
        virtual void run();

    protected:

        //methods above delegate behaviour to the methods below so that you can override it in a subclass

        //initialize sfml rendering context
        virtual void _initializeWindow();
        //print info about the current driver version etc
        virtual void _printVersionInfo();
        //initialize the extension wrangler
        virtual void _initializeGlew();
        //initialize our OpenGL settings
        virtual void _initializeOpenGL();
        //initialize a scene root to which we can attach/add objects
        virtual void _initializeWorld();
        //delete existing world and initialize a new one
        virtual void _resetWorld();

        //initialize the actual scene, to be done by a subclass
        virtual void _initializeScene() = 0;

        //call update on all game objects in the display root
        virtual void _update();
        virtual void _lateUpdate();
        //render all game objects in the display root
//        virtual void _render();
        //process any sfml window events (see SystemEventDispatcher/Listener)
        virtual void _processEvents();

		static sf::RenderWindow* _window;  //sfml window to render into
		RenderPipeline* _renderPipeline;        //the renderer class to render the world
		bool _running;
};

#endif // ABSTRACTGAME_H
