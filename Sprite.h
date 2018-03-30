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
#include <initializer_list>
#include <vector>
#include <map>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>


class Animation {
public:
	Animation();
	Animation(int yoff, bool loop, std::initializer_list<int> frames);
	
	int yoff;
	bool loop;
	unsigned int elapsed;
	std::vector<int> frames;

	void update();
	void reset();
	int currentFrame();
};


class Sprite {
public:
	Sprite();
	Sprite(std::string & path, int w, int h);
	~Sprite();

	static unsigned int textureIDCounter;
	unsigned int textureID;

	std::string path;
	SDL_Texture * sdl_texture;

	Animation currentAnim;
	std::map<std::string, Animation> animations;

	int w, h;
	int offx, offy;

	void addAnim(const std::string & name, int yoff, bool loop, std::initializer_list<int> frames);
	void setAnim(const std::string & name);

	void init();
	bool loadFromFile(const std::string & path, int w, int h);
	void destroy();

};


#endif // IMAGE_H