#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Game.h"
#include "Logger.h"
#include "Renderer.h"
#include "Entity.h"


Camera::Camera() {

}


Camera::~Camera() {

}


void Camera::init() {
	pos.reset();

	isFollowing = false;
	target.reset();
	followOffset.reset();
}


void Camera::update() {
	// Center camera on target
	// TODO this update call happens every time Render is called
	// this could be bad
	// I need to add in that extrapolation feature in renderer
	// Camera would have to take advantage of that too or it would fall behind :C
	if (auto targetLock = target.lock()) {
		Vector windowSize((float)Game::window->windowWidth / Game::renderer->scaleFactor, 
						  (float)Game::window->windowHeight / Game::renderer->scaleFactor);

		// TODO make camera following smooth
		pos = targetLock->pos + followOffset + (targetLock->size - windowSize) / 2;
	}

	// TODO shaking can happen here, with random perturbations in camera position
}


void Camera::moveTo(Vector to) {
	isFollowing = false;
	target.reset();

	Vector windowSize((float)Game::window->windowWidth / Game::renderer->scaleFactor,
						(float)Game::window->windowHeight / Game::renderer->scaleFactor);

	pos = to - windowSize / 2;
}


void Camera::follow(std::weak_ptr<Entity> targ) {
	target = targ;
	isFollowing = true;
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
