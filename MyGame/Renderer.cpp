#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Game.h"
#include "Logger.h"
#include "Renderer.h"
#include "Entity.h"


Camera::Camera() {

}


Camera::~Camera() {
	target = nullptr;
}


void Camera::init() {
	pos.reset();

	follow = false;
	target = nullptr;
	off.reset();
}


void Camera::update() {
	// Center camera on target
	if (follow && target != nullptr) {
		pos.set(target->pos.xf() + target->size.xf() / 2 - Game::window->windowWidth / Game::renderer->scaleFactor / 2 + off.xf(),
				target->pos.yf() + target->size.yf() / 2 - Game::window->windowHeight / Game::renderer->scaleFactor / 2 + off.yf());
	}
}


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

	camera.init();

	return true;
}


void Renderer::render() {
	camera.update();

	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(sdl_renderer);

	// render entities
	SDL_Rect src;
	SDL_Rect dst;
	for (auto i = Game::world->entities.begin(); i != Game::world->entities.end(); ++i) {
		Entity & cur = **i;

		if (cur.visible && cur.active) {
			src.x = cur.sprite.w * cur.sprite.currentAnim.currentFrame();
			src.y = cur.sprite.h * cur.sprite.currentAnim.yoff;
			src.w = cur.sprite.w;
			src.h = cur.sprite.h;

			// The destination here is scaled up by scaleFactor (usually 3)
			dst.x = (cur.pos.x() + cur.sprite.offx - camera.pos.x()) * scaleFactor;
			dst.y = (cur.pos.y() + cur.sprite.offy - camera.pos.y()) * scaleFactor;
			dst.w = cur.sprite.w * scaleFactor;
			dst.h = cur.sprite.h * scaleFactor;

			SDL_RenderCopy(sdl_renderer, (*i)->sprite.sdl_texture, &src, &dst);
		}
	}

	// render ui
	// TODO make UI

	SDL_RenderPresent(sdl_renderer);
}
