#ifndef GAME_H
#define GAME_H


#include <SDL/SDL.h>
#include <memory>

#include "Window.h"
#include "Renderer.h"
#include "Logger.h"
#include "World.h"


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
	//static std::unique_ptr<Input>    input;
	static std::unique_ptr<World>    world;
};

#endif // GAME_H