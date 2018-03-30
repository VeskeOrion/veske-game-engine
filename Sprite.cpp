#include "Sprite.h"
#include "Game.h"


unsigned int Sprite::textureIDCounter = 0;


Sprite::Sprite() {
	init();
	loadFromFile("unkown.png", 64, 64); // hardcoded if no image is given
}


Sprite::Sprite(std::string & path, int w, int h) {
	init();
	loadFromFile(path, w, h);
}


Sprite::~Sprite() {
	destroy();
}


void Sprite::addAnim(const std::string & name, int yoff, bool loop, std::initializer_list<int> frames) {
	Animation anim(yoff, loop, frames);
	animations.insert(std::pair<std::string, Animation>(name, anim));
}


void Sprite::setAnim(const std::string & name) {
	auto a = animations.find(name);
	if (a != animations.end()) {
		currentAnim = a->second;
		currentAnim.reset();
	}
	else {
		Game::logger << "Could not find the specified animation " << name << "\n";
	}
}


void Sprite::init() {
	textureID = textureIDCounter;
	++textureIDCounter;

	path = "";
	sdl_texture = nullptr;
	
	Animation idleAnim;
	animations.insert(std::pair<std::string, Animation>("idle", idleAnim));
	currentAnim = animations.at("idle");

	w = h = 64;
	offx = offy = 0;
}


bool Sprite::loadFromFile(const std::string & path, int w, int h) {
	destroy();

	SDL_Surface * surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		Game::logger << "Could not load image " << path << " from file! SDL_image Error: " << IMG_GetError() << "\n";
		return false;
	}

	sdl_texture = SDL_CreateTextureFromSurface(Game::renderer->sdl_renderer, surface);
	if (sdl_texture == NULL) {
		Game::logger << "Could not create texture " << path << "! SDL Error: " << SDL_GetError() << "\n";
		SDL_FreeSurface(surface);
		return false;
	}

	this->w = w;
	this->h = h;

	SDL_FreeSurface(surface);
	this->path = path;

	return true;
}


void Sprite::destroy() {
	SDL_DestroyTexture(sdl_texture);
	sdl_texture = nullptr;
}


Animation::Animation() {
	yoff = 0;
	loop = false;

	frames.push_back(0);

	elapsed = 0;
}


Animation::Animation(int yoff, bool loop, std::initializer_list<int> frames) {
	this->yoff = yoff;
	this->loop = loop;

	this->frames.insert(this->frames.begin(), frames);

	this->elapsed = 0;
}


void Animation::update() {
	if (elapsed < frames.size() - 1)
		++elapsed;
	if (elapsed >= frames.size() - 1 && loop)
		elapsed = 0;
}


void Animation::reset() {
	elapsed = 0;
}


int Animation::currentFrame() {
	return frames.at(elapsed);
}