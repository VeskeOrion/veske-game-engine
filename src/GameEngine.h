//----------------------------------------------------------------------------------------//
// GameEngine.h
// Represents the GameEngine class, which is what wraps video, audio, and input into one
// neat class. The game can be started by calling the start() function after creating a
// GameEngine object. Everything inside of the run() function's outer loop will be done as
// fast as the computer will allow. Everything inside the inner loop will only happen every
// _dt milliseconds. Don't make more than one of this class.
//----------------------------------------------------------------------------------------//


#ifndef GAMEENGINE_H
#define GAMEENGINE_H


#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>


typedef int int32;
typedef unsigned int uint32;
typedef long int64;
typedef unsigned long uint64;


enum class GameStatus {
	RUNNING, ENDED
};


class GameEngine {
protected:
	SDL_Window  * _window; // the operating system window
	SDL_Surface * _screen; // the viewport the game dispalys on
	SDL_Event     _currentEvent;

	uint32 _screenWidth;
	uint32 _screenHeight;
	uint32 _gameTime; // total ms elapsed
	uint32 _lastTickTime; // 
	int32 _dt; // time between game engine updates
	int32 _timeSinceLastTick; // time since last game engine update (can be neg)
	//uint32 _gameTicks = 0;  // total ticks elapsed

	std::string _gameName;

	GameStatus _gameStatus;

	bool _init();
	void _end();
	void _run();
	void _tick();
	void _render();
	void _processInput();

public:
	GameEngine();
	~GameEngine();
	void start();
};


#endif //GAMEENGINE_H
