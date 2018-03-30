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

	// render entiries
	SDL_Rect src;
	SDL_Rect dst;
	for (auto i = Game::world->entities.begin(); i != Game::world->entities.end(); ++i) {
		Entity & cur = **i;

		if (cur.visible && cur.active) {
			src.x = cur.sprite.w * cur.sprite.currentAnim.currentFrame(); // these will change with anim frames
			src.y = cur.sprite.h * cur.sprite.currentAnim.yoff; // these will change with anim frames
			src.w = cur.sprite.w; // these will probably stay the same
			src.h = cur.sprite.h; // these will probably stay the same

			dst.x = (cur.pos.x() + cur.sprite.offx) * scaleFactor;
			dst.y = (cur.pos.y() + cur.sprite.offy) * scaleFactor;
			dst.w = cur.sprite.w * scaleFactor; // these will probably stay the same
			dst.h = cur.sprite.h * scaleFactor; // these will probably stay the same

			SDL_RenderCopy(sdl_renderer, (*i)->sprite.sdl_texture, &src, &dst);
		}
	}

	SDL_RenderPresent(sdl_renderer);
}
