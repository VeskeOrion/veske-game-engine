#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "Game.h"
#include "Logger.h"
#include "Renderer.h"
#include "Entity.h"


Camera::Camera() {
	zoom = defaultZoom;
}


Camera::~Camera() {

}


void Camera::init() {
	zoom = defaultZoom;

	pos.reset();

	isFollowing = false;
	target.reset();
	followOffset.reset();
}


void Camera::update() {
	if (zoom < 0.1f)
		zoom = 0.1f;
	// Center camera on target
	// TODO this update call happens every time Render is called
	// this could be bad
	// I need to add in that extrapolation feature in renderer
	// Camera would have to take advantage of that too or it would fall behind :C
	if (auto targetLock = target.lock()) {
		Vector windowSize((float)Game::window->windowWidth  / zoom, 
						  (float)Game::window->windowHeight / zoom);

		// TODO make camera following smooth
		//Vector toDestination = targetLock->pos + followOffset + (targetLock->size - windowSize) / 2;
		//pos = pos + (toDestination - pos) * 0.001f;
		pos = targetLock->pos + followOffset + (targetLock->size - windowSize) / 2;

	}
	else {
		isFollowing = false;
		target.reset();
		followOffset.reset();
	}

	// TODO shaking can happen here, with random perturbations in camera position
}


void Camera::moveTo(Vector to) {
	isFollowing = false;
	target.reset();

	Vector windowSize((float)Game::window->windowWidth  / zoom,
					  (float)Game::window->windowHeight / zoom);

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

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

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
			// The src rectangle is the place in the spritesheet we want to render from
			src.x = cur.sprite.w * cur.sprite.currentAnim.currentFrame();
			src.y = cur.sprite.h * cur.sprite.currentAnim.yoff;
			src.w = cur.sprite.w;
			src.h = cur.sprite.h;

			// The dest rectangle is the place on the screen we want to render to
			dst.x = (int) std::round((cur.pos.x() + cur.sprite.offx - camera.pos.xf()) * camera.zoom);
			dst.y = (int) std::round((cur.pos.y() + cur.sprite.offy - camera.pos.yf()) * camera.zoom);
			dst.w = (int) std::round(cur.sprite.w * camera.zoom);
			dst.h = (int) std::round(cur.sprite.h * camera.zoom);

			SDL_RenderCopy(sdl_renderer, (*i)->sprite.sdl_texture, &src, &dst);
		}
	}

	// TODO render ui
	// TODO make UI

	SDL_RenderPresent(sdl_renderer);
}


//std::shared_ptr<Sprite> Renderer::createSprite(const std::string & path, int w, int h) {
//	std::shared_ptr<Sprite> sprite;
//	sprite = findSprite(path);
//
//	if (!sprite) {
//		sprite.reset(new Sprite(path, w, h));
//		sprites.push_back(sprite);
//	}
//
//	return sprite;
//}
//
//
//std::shared_ptr<Sprite> Renderer::findSprite(const std::string & path) {
//	std::shared_ptr<Sprite> s = nullptr;
//	for (auto i = sprites.begin(); i != sprites.end(); ++i)
//		if ((*i)->path.compare(path) == 0)
//			return (*i);
//	return nullptr;
//}