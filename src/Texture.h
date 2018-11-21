//----------------------------------------------------------------------------------------//
// Image.h
// Contains a class that represents an image. Usually, each Entity will have an Image that
// corresponds to its visual representation. Images can be loaded and unloaded if desired,
// and also have an offset x and y so that they can be positioned relative to their parent
// entities.
//----------------------------------------------------------------------------------------//


#ifndef TEXTURE_H
#define TEXTURE_H


#include <string>
#include <map>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>


class Texture {
public:
	Texture();
	Texture(const std::string & path, int w, int h);
	~Texture();

    SDL_Surface * sdl_surface;
	SDL_Texture * sdl_texture;

	std::string path;
	int w, h;

	void init();
	bool loadFromFile(const std::string & path, int w, int h);
	void destroy();
};


#endif // TEXTURE_H