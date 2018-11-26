//----------------------------------------------------------------------------------------//
// Window.h
// Contains a class that sets up the windowing system. This class creates the window pane
// via communicating with the operating system.
// Access this class via Game::window.
//----------------------------------------------------------------------------------------//


#ifndef WINDOWING_H
#define WINDOWING_H


#include <string>
#include <iostream>

#include <SDL.h>


class Window {
public:
	Window();
	~Window();

	SDL_Window * sdl_window;

	std::string windowTitle;
	int windowWidth = 1280;
	int windowHeight = 720;

	bool init();
};


#endif // WINDOWING_H