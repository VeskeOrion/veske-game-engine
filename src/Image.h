//----------------------------------------------------------------------------------------//
// Image.h
// Contains a class that represents an image. Usually, each Entity will have an Image that
// corresponds to its visual representation. Images can be loaded and unloaded if desired,
// and also have an offset x and y so that they can be positioned relative to their parent
// entities.
//----------------------------------------------------------------------------------------//


#ifndef IMAGE_H
#define IMAGE_H


#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


// TODO perhaps I can put this class inside Renderer. I could make it so
// any object that has an Image only has a shared/weak ptr to a image instead.
// The Renderer would hold a list/vector/array (probably something const-time
// accessible) of shared ptrs to all the images that have been loaded. An entity
// 'has' an image when it has been assigned a Image from the Renderer list. This
// way all image loading is centralized, and entites would have to lease out
// images instead of owning their own. Images could be reused between multiple
// entites by all just sharing the same image.
// To create an image, one might have
// in the Entity class this:
// In Entity.h: std::weak_ptr<Entity> image;
// In Entity.cpp: image = Game::renderer->load("path.png");
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