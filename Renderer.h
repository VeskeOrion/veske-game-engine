//----------------------------------------------------------------------------------------//
// Renderer.h
// Contains a class that renders all of the Entities in the World, as well as Terrain (in
// development) and other graphical effects like Lights (in development).
// This class also manages the leasing of Image objects and keeps them in a centalized
// location so they do not need to be loaded multiple times (in development).
// Access this class via Game::renderer.
//----------------------------------------------------------------------------------------//


#ifndef RENDERER_H
#define RENDERER_H


#include <string>
#include <memory>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


class Renderer {
public:
	Renderer();
	~Renderer();

	SDL_Renderer * sdl_renderer;

	bool init();
	void render();
	void renderText(std::string text, int size);
};


class Text {
	Text();
	~Text();

	TTF_Font * font;
	std::string text;
};

#endif //RENDERER_H
