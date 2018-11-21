#include "Texture.h"
#include "Game.h"


//unsigned int Texture::textureIDCounter = 0;


Texture::Texture() {
	init();
}


Texture::Texture(const std::string & path, int w, int h) {
	init();
	loadFromFile(path, w, h);
}


Texture::~Texture() {
	destroy();
}


void Texture::init() {
	destroy();

	path = "";
	sdl_texture = nullptr;

	w = h = 0;

	Game::logger << "Creating a texture.\n";
}


// Loads a Texture from the specified path, where each Texture has width w and height h
bool Texture::loadFromFile(const std::string & path, int w, int h) {
	SDL_Surface * new_surface = IMG_Load(path.c_str());
	if (new_surface == NULL) {
		Game::logger << "Could not load image " << path << " from file! SDL_image Error: " << IMG_GetError() << "\n";
		return false;
	}

	SDL_Texture * new_texture = SDL_CreateTextureFromSurface(Game::renderer->sdl_renderer, new_surface);
	if (new_texture == NULL) {
		Game::logger << "Could not create texture " << path << "! SDL Error: " << SDL_GetError() << "\n";
		SDL_FreeSurface(new_surface);
		return false;
	}

	destroy();

	sdl_texture = new_texture;
    sdl_surface = new_surface;

	this->path = path;
	this->w = w;
	this->h = h;

	return true;
}


void Texture::destroy() {
	if (sdl_surface != nullptr) {
		SDL_FreeSurface(sdl_surface);
		sdl_surface = nullptr;
	}
    if (sdl_texture != nullptr) {
		SDL_DestroyTexture(sdl_texture);
		sdl_texture = nullptr;
	}
}
