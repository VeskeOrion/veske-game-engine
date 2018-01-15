#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Image {
public:
	Image();
	Image(const std::string & path);
	~Image();

	unsigned int offx, offy, w, h;

	SDL_Texture * sdl_texture = nullptr;

	bool load(const std::string & path);
	void unload();

	// TODO add size, offset, and support for animation
};

#endif // IMAGE_H