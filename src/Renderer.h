#ifndef GAMEENGINE_H
#define GAMEENGINE_H


class Renderer {
public:
	Renderer();
	~Renderer();

	SDL_Renderer * sdl_renderer;

	bool init();

	void render();

};


#endif //GAMEENGINE_H