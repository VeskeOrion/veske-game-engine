//----------------------------------------------------------------------------------------//
// GameEngine.cpp
// Represents the GameEngine class, which is what wraps video, audio, and input into one
// neat class. The game can be started by calling the start() function after creating a
// GameEngine object. Everything inside of the run() function's first loop will be done as
// fast as the computer will allow. Everything inside the second loop will only happen every
// _dt milliseconds. Don't make more than one of this class.
//----------------------------------------------------------------------------------------//


#include <iostream>
#include "GameEngine.h"
#include "GameLog.h"


/** Constructs a new empty GameEngine */
GameEngine::GameEngine() {
	_window = nullptr;
	_screen = nullptr;

	_gameName = "My Game";

	_screenWidth = 1280;
	_screenHeight = 720;

	_gameTime = 0;
	_dt = 20;
	_timeSinceLastTick = 20;

	memset(&_currentEvent, 0, sizeof(_currentEvent));
}


/** Destroys a GameEngine object and frees any memory it has stored */
GameEngine::~GameEngine() {

}


/** Runs the game so long as it is still being played, this should be called
	by main(). Maybe this could return an int that contains the status of the
	game upon closing/crashing */
void GameEngine::start() {
	if (_init()) {
		_gameStatus = GameStatus::RUNNING;

		_run();

		_end();
	}
	else {
		GameLog::err("Aborted the initialization because of the above error.");
	}
}


/** Fills the member variables of the GameEngine and initializes a window for
	the game */
bool GameEngine::_init() {
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
		GameLog::err("SDL failed to initialize!");
		return false;
	}

	// Create a window
	_window = SDL_CreateWindow(_gameName.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	if (_window == nullptr) {
		GameLog::err("SDL failed to create a window!");
		return false;
	}
	
	// TODO decide if I need the below code
	// Sets OpenGL context to the current window
	//SDL_GLContext glcontext = SDL_GL_CreateContext(_window);
	//if (glcontext == nullptr) {
	//	GameLog::err("Failed to attach an OpenGL context to the window.");
	//	return false;
	//}

	// TODO decide if I need the below code
	// Initializes GL Extension Wrangler
	//if (glewInit() != GLEW_OK) {
	//	GameLog::err("Failed to initialize GLEW.");
	//	return false;
	//}

	// TODO decide if I need the below code
	// Enable OpenGL double buffering
	// SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// SDL_GL_SetSwapInterval(0);
	
	// TODO decide if I need the below code
	// Set background color
	//glClearColor(.0f, .0f, .0f, 1.0f);

	GameLog::log("Game systems all successfully started.");

	// Tell the game to begin looping
	return true;
}


/** Clears the member variables of the GameEngine and quits SDL */
void GameEngine::_end() {
	if (_window != nullptr)
		SDL_DestroyWindow(_window);
	_window = nullptr;

	GameLog::log("Shutdown successful. Closing.");

	SDL_Quit();
}


/** The main game loop */
void GameEngine::_run() {
	while (_gameStatus == GameStatus::RUNNING) {
		_gameTime = SDL_GetTicks();

		while (_timeSinceLastTick >= _dt) {
			_tick();
			_lastTickTime = SDL_GetTicks();
			_timeSinceLastTick -= _dt;
		}
		_render(); //  TODO decide if this should be inside the dt loop

		_timeSinceLastTick += SDL_GetTicks() - _gameTime;
	}
}


/** Advances the game state forward one step */
void GameEngine::_tick() {
	_processInput();
	// put entity updates here
}

/** Draws all of the current game objects onto the screen */
void GameEngine::_render() {
	// put entity drawing, background drawing, lighting, etc. here

	// SDL_GL_SwapWindow(_window); // TODO figure out what this is, decide if it's needed
}


/** Checks what sort of input the user is currently providing to the program */
void GameEngine::_processInput() {
	while (SDL_PollEvent(&_currentEvent)) {
		switch (_currentEvent.type) {
			case SDL_QUIT: {
				_gameStatus = GameStatus::ENDED;
			}
			break;

			case SDL_MOUSEMOTION: {

			}
			break;

			case SDL_MOUSEBUTTONDOWN: {
				
			}
			break;

			case SDL_KEYDOWN: {
				
			}
			break;
		}
	}
}
