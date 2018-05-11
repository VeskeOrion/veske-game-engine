#include "Sprite.h"
#include "Game.h"


//unsigned int Sprite::textureIDCounter = 0;


Sprite::Sprite() {
	init();
}


Sprite::Sprite(std::string & path, int w, int h) {
	init();
	loadFromFile(path, w, h);
}


Sprite::~Sprite() {
	destroy();
}


// Creates an animation with name name, a vertical index in the spritesheet of yoff,
// a bool loop that determines if the animation loops at the end, and a bracketed
// initializer list of the x indices in the spritesheet that play each frame, i.e.
// {0, 1, 2, 3, 2, 1, 0}
void Sprite::addAnim(const std::string & name, int yoff, bool loop, std::initializer_list<int> frames) {
	Animation anim(yoff, loop, frames);
	anim.name = name;
	animations.insert(std::pair<std::string, Animation>(name, anim));
}


// Sets the current animation that will play starting next tick and resets the animation
void Sprite::setAnim(const std::string & name) {
	auto a = animations.find(name);
	if (a != animations.end()) {
		currentAnim = a->second;
		currentAnim.replay();
	}
	else {
		Game::logger << "Could not find the specified animation: " << name << "\n";
	}
}


void Sprite::clearAnims() {
	currentAnim.init();
	animations.clear();
	animations.insert(std::pair<std::string, Animation>("default", currentAnim));
}


void Sprite::init() {
	destroy();

	clearAnims();

	path = "";
	sdl_texture = nullptr;

	w = h = 0;
	offx = offy = 0;
	sheetWidth = sheetHeight = 0;
}


// Loads a sprite sheet from the specified path, where each sprite has width w and height h
bool Sprite::loadFromFile(const std::string & path, int w, int h) {

	SDL_Surface * surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		Game::logger << "Could not load image " << path << " from file! SDL_image Error: " << IMG_GetError() << "\n";
		return false;
	}

	SDL_Texture * newsdl_texture = SDL_CreateTextureFromSurface(Game::renderer->sdl_renderer, surface);
	if (newsdl_texture == NULL) {
		Game::logger << "Could not create texture " << path << "! SDL Error: " << SDL_GetError() << "\n";
		SDL_FreeSurface(surface);
		return false;
	}

	destroy();
	SDL_FreeSurface(surface);

	clearAnims();

	this->path = path;
	sdl_texture = newsdl_texture;

	this->w = w;
	this->h = h;
	offx = offy = 0;
	this->sheetWidth = surface->w;
	this->sheetHeight = surface->h;

	return true;
}


void Sprite::destroy() {
	if (sdl_texture != nullptr) {
		SDL_DestroyTexture(sdl_texture);
		sdl_texture = nullptr;
	}
}


Animation::Animation() {
	init();
}


Animation::Animation(int yoff, bool loop, std::initializer_list<int> frames) {
	init();
	setup(yoff, loop, frames);
}


void Animation::init() {
	yoff = 0;
	loop = false;

	frames.clear();
	frames.push_back(0);

	name = "default";
}


void Animation::setup(int yoff, bool loop, std::initializer_list<int> frames) {
	this->yoff = yoff;
	this->loop = loop;

	this->frames.clear();
	this->frames.insert(this->frames.begin(), frames); // I love the std lib

	this->elapsed = 0;
}


void Animation::update() {
	if (elapsed < frames.size() - 1)
		++elapsed;
	if (elapsed >= frames.size() - 1 && loop)
		elapsed = 0;
}


void Animation::replay() {
	elapsed = 0;
}


int Animation::currentFrame() {
	return frames.at(elapsed);
}