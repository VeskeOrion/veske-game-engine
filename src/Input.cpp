#include "Input.h"
#include "Game.h"


Input::Input() {

}


Input::~Input() {

}


bool Input::init() {
	// TODO delete this?
	SDL_ShowCursor(SDL_DISABLE);

	return true;
}


bool Input::getKeyDown(Key key) {
	return keypresses[key].down;
}


bool Input::getKeyTapped(Key key) {
	return keypresses[key].down && keypresses[key].duration == 0;
}


unsigned int Input::getKeyDownDuration(Key key) {
	return keypresses[key].duration;
}


void Input::processInput() {
	// Update key durations for all keys
	for (unsigned int i = 0; i < NUM_KEYS; ++i)
		if (keypresses[i].down)
			++keypresses[i].duration;
	tapped.clear();

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT: {
				Game::world->done = true;
			} break;

			case SDL_MOUSEMOTION: {
				handleMouseMotion(e);
			} break;

			case SDL_MOUSEBUTTONDOWN: {
				handleMouseButtonDown(e);
			} break;

			case SDL_MOUSEBUTTONUP: {
				handleMouseButtonUp(e);
			} break;

			case SDL_KEYDOWN: {
				handleKey(e, KEY_DOWN);
			}  break;

			case SDL_KEYUP: {
				handleKey(e, KEY_UP);
			}  break;
		}
	}
}


void Input::handleMouseMotion(SDL_Event & e) {
	//Game::logger << "Motion: x=" << e.motion.x << ", y= " << e.motion.y << "\n";
	mouseX = e.motion.x;
	mouseY = e.motion.y;
}


void Input::handleMouseButtonDown(SDL_Event & e) {
	//Game::logger << "ClickDown\n";
}


void Input::handleMouseButtonUp(SDL_Event & e) {
	//Game::logger << "ClickUp\n";
}


void Input::handleKey(SDL_Event & e, bool down) {
	//Game::logger << "Key " << SDL_GetKeyName(e.key.keysym.sym) << "\n";

	// TODO find out if the below is 100% safe

	// Try to map the SDL_K to an array index (Key) in keypresses
	auto mapElement = SDL_KToKey.find(e.key.keysym.sym);
	
	// If we we cannot map the SDL_K to a Key, return
	if (mapElement == SDL_KToKey.end())
		return;
	
	// Else, we have mapped a the SDL_K to a Key
	Key key = mapElement->second;

	// Set the down status of the key, and clear the down duration if key goes up
	// Because key durations are incremented at the start of each frame, before input is processed,
	// newly tapped keys will have a down status of true and a duration of 0.
	keypresses[key].down = down;
	keypresses[key].duration = keypresses[key].duration * down;

	if (keypresses[key].down == true && keypresses[key].duration == 0)
		tapped.push_back(key);
}