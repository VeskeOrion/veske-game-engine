#include "Input.h"
#include "Game.h"


Input::Input() {

}


Input::~Input() {
	if (controller != nullptr)
		SDL_GameControllerClose(controller);
}


bool Input::init() {
	// TODO delete this?
	//SDL_ShowCursor(SDL_DISABLE);

	// TODO this only gets one controller
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			SDL_GameControllerEventState(SDL_ENABLE);
		}
	}

	return true;
}


Vector Input::getMousePos() {
	return mousePos;
}


Vector Input::getMovementAxes() {
	return movementAxes;
}


bool Input::getAction(InputMapping action) {
	return actions[action].occurring;
}


bool Input::getActionTapped(InputMapping action) {
	return actions[action].occurring && actions[action].duration == 0;
}


unsigned int Input::getActionDuration(InputMapping action) {
	return actions[action].duration;
}


bool Input::getRawKey(RawKey key) {
	return keyPresses[key].down;
}


bool Input::getRawKeyTapped(RawKey key) {
	return keyPresses[key].down && keyPresses[key].duration == 0;
}


unsigned int Input::getRawKeyDownDuration(RawKey key) {
	return keyPresses[key].duration;
}


void Input::processInput() {
	// Update key durations for all keys
	for (unsigned int i = 0; i < NUM_KEYS; ++i) {
		if (keyPresses[i].down)
			++keyPresses[i].duration;
	}
	tappedKeys.clear();
	for (unsigned int i = 0; i < NUM_MOUSEBUTTONS; ++i) {
		if (mouseButtonPresses[i].down)
			++mouseButtonPresses[i].duration;
	}
	tappedMouseButtons.clear();
	for (unsigned int i = 0; i < NUM_ACTIONS; ++i) {
		if (actions[i].occurring)
			++actions[i].duration;
	}
	tappedActions.clear();

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
				handleMouseButton(e, KEY_DOWN);
			} break;

			case SDL_MOUSEBUTTONUP: {
				handleMouseButton(e, KEY_UP);
			} break;

			case SDL_KEYDOWN: {
				handleKey(e, KEY_DOWN);
			} break;

			case SDL_KEYUP: {
				handleKey(e, KEY_UP);
			} break;

			case SDL_CONTROLLERAXISMOTION: {
				handleControllerAxisMotion(e);
			} break;

			case SDL_CONTROLLERBUTTONDOWN: {
				handleControllerButton(e, KEY_DOWN);
			} break;

			case SDL_CONTROLLERBUTTONUP: {
				handleControllerButton(e, KEY_UP);
			} break;
		}
	}

	movementAxes.set(actions[LEFT].magnitude + actions[RIGHT].magnitude,
					 actions[UP  ].magnitude + actions[DOWN ].magnitude);
}


void Input::handleMouseMotion(SDL_Event & e) {
	mousePos.set((float)e.motion.x, (float)e.motion.y);
}


void Input::handleControllerAxisMotion(SDL_Event & e) {
	// TODO
}


void Input::handleMouseButton(SDL_Event & e, bool down) {
	// TODO i might need to set mouseX and mouseY from the sdl button.x and button.x in e

	// Raw mouse button input
	auto buttonMap = SDL_ButtonToRawMouseButton.find(e.button.button); // map sdl button to game button
	if (buttonMap == SDL_ButtonToRawMouseButton.end())
		return;

	// Set down status of the button, clear the duration if button goes up
	RawMouseButton mb = buttonMap->second;
	mouseButtonPresses[mb].down = down;
	mouseButtonPresses[mb].duration = mouseButtonPresses[mb].duration * down;

	if (mouseButtonPresses[mb].down && mouseButtonPresses[mb].duration == 0)
		tappedMouseButtons.push_back(mb);

	// Game action mapping
	auto actionMap = RawMouseButtonToAction.find(mb);
	if (actionMap == RawMouseButtonToAction.end())
		return;

	// Set occurring status of the action, clear the duration if action ends
	InputMapping action = actionMap->second;
	actions[action].occurring = down;
	actions[action].duration = actions[action].duration * down;
	actions[action].magnitude = 1.0f * down;

	switch (action) {
		case UP: {
			actions[action].magnitude = -1.0f * down;
		} break;

		case DOWN: {
			actions[action].magnitude = 1.0f * down;
		} break;

		case LEFT: {
			actions[action].magnitude = -1.0f * down;
		} break;

		case RIGHT: {
			actions[action].magnitude = 1.0f * down;
		} break;
	}
}


void Input::handleKey(SDL_Event & e, bool down) {
	// Raw keyboard input
	auto keyMap = SDL_KToRawKey.find(e.key.keysym.sym); // map sdl key to game key
	if (keyMap == SDL_KToRawKey.end())
		return;
	
	// Set the down status of the key, and clear the duration if key goes up
	RawKey key = keyMap->second;
	keyPresses[key].down = down;
	keyPresses[key].duration = keyPresses[key].duration * down;

	if (keyPresses[key].down && keyPresses[key].duration == 0)
		tappedKeys.push_back(key);


	// Game action mapping
	auto actionMap = RawKeyToAction.find(key); // map game key to game action
	if (actionMap == RawKeyToAction.end())
		return;

	// Set the occurring status of the action, and clear the duration if action ends
	InputMapping action = actionMap->second;
	actions[action].occurring = down;
	actions[action].duration = actions[action].duration * down;
	actions[action].magnitude = 1.0f * down;

	// TODO put tappedActions here?

	// For keys that modify movement axes, default to speed of 1.0f;
	switch (action) {
		case UP: {
			actions[action].magnitude = -1.0f * down;
		} break;

		case DOWN: {
			actions[action].magnitude = 1.0f * down;
		} break;
		
		case LEFT: {
			actions[action].magnitude = -1.0f * down;
		} break;

		case RIGHT: {
			actions[action].magnitude = 1.0f * down;
		} break;
	}
}


void Input::handleControllerButton(SDL_Event & e, bool down) {
	// TODO
}