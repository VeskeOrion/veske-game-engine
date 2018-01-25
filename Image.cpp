#include "Image.h"
#include "Game.h"


Image::Image() {
	// TODO delete this
	load("unkown.png");
	offx = offy = 0;
	w = h = 64;
}


Image::Image(const std::string & path) {
	load(path);
}


Image::~Image() {
	unload();
}


bool Image::load(const std::string & path) {
	unload();
	
	SDL_Surface * surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		Game::logger << "Could not load image " << path << "! SDL_image Error: " << IMG_GetError() << "\n";
		return false;
	}

	sdl_texture = SDL_CreateTextureFromSurface(Game::renderer->sdl_renderer, surface);
	if (sdl_texture == NULL) {
		Game::logger << "Could not create texture " << path <<"! SDL Error: " << SDL_GetError() << "\n";
		SDL_FreeSurface(surface);
		return false;
	}

	SDL_FreeSurface(surface);
	return true;
}


void Image::unload() {
	SDL_DestroyTexture(sdl_texture);
	sdl_texture = nullptr;
}