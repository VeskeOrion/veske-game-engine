//----------------------------------------------------------------------------------------//
// Image.h
// Contains a class that represents an image. Usually, each Entity will have an Image that
// corresponds to its visual representation. Images can be loaded and unloaded if desired,
// and also have an offset x and y so that they can be positioned relative to their parent
// entities.
//----------------------------------------------------------------------------------------//


#ifndef SPRITE_H
#define SPRITE_H


#include <string>
#include <initializer_list>
#include <vector>
#include <map>
#include <memory>

#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

#include "Texture.h"


// class Animation {
// public:
// 	Animation();
// 	Animation(int yoff, bool loop, std::initializer_list<int> frames);
	
// 	std::string name;

// 	int yoff; // how far down the spritesheet an animation is located
// 	bool loop; // if an animation should loop when it has reached its final frame
// 	std::vector<int> frames; // a vector of x indices along the spritesheet that are played in order
	
// 	unsigned int elapsed; // how many frames of the animation have played so far

// 	void init();
// 	void setup(int yoff, bool loop, std::initializer_list<int> frames);
// 	void update(); // increments the elapsed variable and resets it to 0 if this anim loops
// 	void replay(); // restarts the animation from the beggining
// 	int currentFrame(); // returns the x index along the spriteshite, aka the index of the current frame
// };


class Sprite {
public:
	Sprite();
	~Sprite();

	std::shared_ptr<Texture> texture;

	//Animation currentAnim; // the animation that the renderer will draw on this sprite
	//std::map<std::string, Animation> animations;

	int w, h;
	int offx, offy;

	// void addAnim(const std::string & name, int yoff, bool loop, std::initializer_list<int> frames);
	// void setAnim(const std::string & name);
	// void clearAnims();

	void init();
	bool loadTexture(const std::string & path, int w, int h);
	void destroy();

};


#endif // SPRITE_H