#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Game.h"
#include "Logger.h"
#include "Renderer.h"
#include "Entity.h"


Renderer::Renderer() {

}


Renderer::~Renderer() {
	TTF_Quit();

	IMG_Quit();

	SDL_DestroyRenderer(sdl_renderer);
	sdl_renderer = nullptr;
}


bool Renderer::init() {
	// Initialize renderer
	sdl_renderer = SDL_CreateRenderer(Game::window->sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == nullptr) {
		Game::logger << "Failed to create a renderer!\n";
		return false;
	}

	// Initialize image library
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		Game::logger << "SDL_image failed to initialize!\n";
		return false;
	}

	// Initialize ttf library
	if (TTF_Init() == -1) {
		Game::logger << "SDL_ttf failed to initialize!\n";
		return false;
	}

	return true;
}


void Renderer::render() {
	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdl_renderer);

	SDL_Rect src;
	SDL_Rect dst;

	auto i = Game::world->entities.begin();
	for (auto i = Game::world->entities.begin(); i != Game::world->entities.end(); ++i) {
		Entity & cur = **i;

		src.x = 0; // these will change with anim frames
		src.y = 0; // these will change with anim frames
		src.w = cur.image.w; // these will probably stay the same
		src.h = cur.image.h; // these will probably stay the same

		dst.x = cur.pos.x() + cur.image.offx;
		dst.y = cur.pos.y() + cur.image.offy;
		dst.w = cur.image.w; // these will probably stay the same
		dst.h = cur.image.h; // these will probably stay the same

		SDL_RenderCopy(sdl_renderer, (*i)->image.sdl_texture, &src, &dst);
	}

	SDL_RenderPresent(sdl_renderer);
}


//void Renderer::createFont(std::string path, int size) {
//
//}
//
//
//void Renderer::renderText(Text text) {
//	TTF_Font * font = TTF_OpenFont("Arial.ttf", 12);
//	if (font == NULL)
//		return;
//
//	SDL_Surface * surface = TTF_RenderText_Blended(font, text.c_str(), {255, 255, 255});
//	SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
//
//	SDL_FreeSurface(surface);
//
//	SDL_RenderCopy
//}