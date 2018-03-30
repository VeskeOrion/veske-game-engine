#include "Window.h"


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
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
		//GameLog::err("SDL failed to initialize!");
		//GameLog::err(SDL_GetError()); // TODO readd this
		return false;
	}

	// Create a window
	sdl_window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_OPENGL);
	if (sdl_window == nullptr) {
		//GameLog::err("SDL failed to create a window!");
		//GameLog::err(SDL_GetError()); // TODO readd this
		return false;
	}

	return true;
}