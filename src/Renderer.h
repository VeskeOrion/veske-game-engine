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


#include <memory>

#include <SDL.h>

#include "Game.h"
#include "Entity.h"
#include "Texture.h"


class Camera {
public:
	Camera();
	~Camera();

	float zoom;
	const float defaultZoom = 10.0f;

	Vector pos;

	bool isFollowing;
	std::weak_ptr<Entity> target;
	Vector followOffset;

	void init(); // TODO destroy function? On all game systems?
	void update();

	void follow(std::weak_ptr<Entity> targ);
	void moveTo(Vector to);

	Vector worldToCamera(Vector point);
	Vector screenToWorld(Vector point);

	//TODO add shake function, with duration, magnitude, etc
};

class Renderer {
public:
	Renderer();
	~Renderer();

	Camera camera;
	std::list<std::shared_ptr<Texture>> textures;

	//std::list<std::shared_ptr<Sprite>> sprites;

	SDL_Renderer * sdl_renderer;

	bool init();
	void render();

	//std::shared_ptr<Sprite> createSprite(const std::string & path, int w, int h);
	//std::shared_ptr<Sprite> findSprite(const std::string & path);
};


#endif //RENDERER_H
