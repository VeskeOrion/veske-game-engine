//----------------------------------------------------------------------------------------//
// Game.h
// Contains a class that represents the game and all of its subsystems. This class is
// essentially the main method (in fact, the main method is in Game.cpp). It contains static
// unique pointers to all of the subsytems of the game: Window, Renderer, Logger, Audio,
// Input, and World. Pointers to all of these subsystems can be accessed via
// Game::subsystem_name, like Game::world->run() or Game::input->getKeyDown(Input::Key::A).
// To start a game, Game::start() must be called, which will initialize all the subsytems
// and run the World.
//----------------------------------------------------------------------------------------//


#ifndef GAME_H
#define GAME_H


#include <memory>

#include <SDL/SDL.h>

#include "Window.h"
#include "Renderer.h"
#include "Logger.h"
#include "World.h"
#include "Input.h"


class Game {
private:
	Game();
	~Game();

public:
	static int start();

	static std::unique_ptr<Window>   window;
	static std::unique_ptr<Renderer> renderer;
	static std::unique_ptr<Logger>   logger;
	//static std::unique_ptr<Audio>    audio;
	static std::unique_ptr<Input>    input;
	static std::unique_ptr<World>    world;
};


#endif // GAME_H