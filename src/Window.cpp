#include "Game.h"


Window::Window() {

}


Window::~Window() {
	SDL_DestroyWindow(sdl_window);
	sdl_window = nullptr;
}


bool Window::init() {
	sdl_window = nullptr;

	windowWidth = 1280;
	windowHeight = 720;

	windowTitle = "Test game!";

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0) {
		Game::logger << "Could not initialize SDL.\n;";
		return false;
	}

	// Create a window
	sdl_window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	if (sdl_window == nullptr) {
		Game::logger << "Could not create a window.\n";
		return false;
	}

	return true;
}