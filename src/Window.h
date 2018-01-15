#ifndef WINDOWING_H
#define WINDOWING_H

#include <string>
#include <SDL/SDL.h>
#include <iostream>

class Window {
public:
	Window();
	~Window();

	SDL_Window * sdl_window;

	int windowWidth = 1280;
	int windowHeight = 720;

	std::string windowTitle;

	bool init();
};

#endif // WINDOWING_H