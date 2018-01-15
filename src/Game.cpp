#include "Game.h"


std::unique_ptr<Logger>      Game::logger = nullptr;
std::unique_ptr<Window>      Game::window = nullptr;
std::unique_ptr<Renderer>    Game::renderer = nullptr;
//std::unique_ptr<Audio>       Game::audio = nullptr;
//std::unique_ptr<Input>       Game::input = nullptr;
std::unique_ptr<World>       Game::world = nullptr;


Game::Game() {

}


Game::~Game() {

}


int Game::start() {
	// TODO if this is too slow, add a loading screen

	Game::logger.reset(new Logger());
	Game::window.reset(new Window());
	Game::renderer.reset(new Renderer());
	//Game::audio.reset(new Audio());
	//Game::input.reset(new Input());
	Game::world.reset(new World());

	Game::logger->init(); // we don't have to abort if logger fails

	if (!Game::window->init())
		return EXIT_FAILURE;

	if (!Game::renderer->init())
		return EXIT_FAILURE;

	Game::world->init(); // TODO move the run function into world, then call world->run

	Game::world->run();

	return EXIT_SUCCESS;
}


int main(int argc, char ** argv) {
	return Game::start();
}