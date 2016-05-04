#include "AbstractGame.hpp"

#include <iostream>
#include <glm.hpp>

#include "mge/core/Input.hpp"
#include "mge/core/Timer.hpp"
#include "mge/core/FPS.hpp"
#include "mge/core/World.hpp"

#include "mge/config.hpp"

using namespace std;

sf::RenderWindow* AbstractGame::_window = 0;

AbstractGame::AbstractGame():_running(false)
{

}

AbstractGame::~AbstractGame()
{
    delete _window;
}

void AbstractGame::initialize() {
    cout << "Initializing engine..." << endl << endl;
    _initializeWindow();
    _printVersionInfo();
    _initializeGlew();
    _initializeOpenGL();
    _initializeWorld();
    _initializeScene();
    cout << endl << "Engine initialized." << endl << endl;
}

///SETUP

void AbstractGame::_initializeWindow() {
	cout << "Initializing window..." << endl;
	_window = new sf::RenderWindow( sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "Sphinx Dream", WINDOW_MODE, sf::ContextSettings(24,8,MSAA,3,3));
	_window->setVerticalSyncEnabled(true);
	_window->clear(sf::Color(0,0,0));
	sf::Texture* texture = new sf::Texture;
	texture->loadFromFile(config::MGE_SPRITE_PATH+ "Loading_Screen.png");
	sf::Sprite* sprite = new sf::Sprite;
	sprite->setTexture(*texture);
	sprite->setTextureRect(sf::IntRect(0,0,1920,1080));
    _window->draw(*sprite);
	_window->display();
    cout << "Window initialized." << endl << endl;
}

void AbstractGame::_printVersionInfo() {
	cout << "Context info:" << endl;
    cout << "----------------------------------" << endl;
    //print some debug stats for whoever cares
    const GLubyte *vendor = glGetString( GL_VENDOR );
    const GLubyte *version = glGetString( GL_VERSION );
    const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
    //nice consistency here in the way OpenGl retrieves values
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL Vendor : %s\n", vendor);
    printf("GL Version (string) : %s\n", version);
    printf("GL Version (integer) : %d.%d\n", major, minor);
    printf("GLSL Version : %s\n", glslVersion);

    cout << "----------------------------------" << endl << endl;
}

void AbstractGame::_initializeGlew() {
	cout << "Initializing GLEW..." << endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
	cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << endl << endl;
}

void AbstractGame::_initializeOpenGL() {

    _renderPipeline = new RenderPipeline();
    cout << "RenderPipeline initialized..." << endl;
}

void AbstractGame::_initializeWorld() {

    //note: replaced by private Instance constructor

    //setup our own renderer
//	cout << "Initializing world..." << endl;
//	_world = new World();
//  cout << "World initialized." << endl << endl;
}

void AbstractGame::_resetWorld() {
//    if (_world != NULL)
//    {
//        delete _world;
//        _world = NULL;
//    }
//    _initializeWorld();
}

///LOOP

void AbstractGame::run()
{
	_running = true;

	while (_running) {
		Timer::update();
		FPS::update();

	    //clear frame, do it here so we can draw debug stuff in any other step etc
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        _update();

        _renderPipeline->render(World::Instance());

        _lateUpdate();

        //swap colorbuffer to screen
        _window->display();

		_processEvents();
	}
}

void AbstractGame::_update() {
    World::Instance()->update(Timer::deltaTime(), glm::mat4());
}

void AbstractGame::_lateUpdate()
{

}

void AbstractGame::_processEvents()
{
	sf::Event event;
	bool exit = false;

    //clear keyDown array
    for (unsigned int i=0; i<sizeof(Input::_keyDown); i++)
    {
        Input::_keyDown[i] = false;
    }

	//we must empty the event queue
	while( _window->pollEvent( event ) ) {
        //give all system event listeners a chance to handle events
        //optionally to be implemented by you...
        //SystemEventDispatcher::dispatchEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                exit = true;
                break;
            case sf::Event::KeyPressed:
                //enter value to that array here
                if (event.key.code == sf::Keyboard::Escape) {
                    exit = true;
                }

                Input::_keyDown[event.key.code] = true;
                break;
            case sf::Event::KeyReleased:
                break;
            case sf::Event::Resized:
                //would be better to move this to the renderer
                //this version implements nonconstrained match viewport scaling
                glViewport(0, 0, event.size.width, event.size.height);
                break;

            default:
                break;
        }
	}

	if (exit) {
        _window->close();
        _running = false;
	}
}



