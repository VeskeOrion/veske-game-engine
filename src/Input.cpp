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
	// TODO this should be done whenever needed if controllers are replugged etc
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			SDL_GameControllerEventState(SDL_ENABLE);
		}
	}

	// TODO set all inputs to false

	return true;
}


Vector Input::getMousePos() {
	return virtualController.mousePos;
}


Vector Input::getMovementAxes() {
	return virtualController.movementAxes;
}


bool Input::getAction(Action action) {
	return virtualController.actions[action].occurring;
}


bool Input::getActionTapped(Action action) {
	return virtualController.actions[action].occurring && virtualController.actions[action].duration == 0;
}


unsigned int Input::getActionDuration(Action action) {
	return virtualController.actions[action].duration;
}


bool Input::getRawKey(RawKeyboardKey key) {
	return keyPresses[key].occurring;
}


bool Input::getRawKeyTapped(RawKeyboardKey key) {
	return keyPresses[key].occurring && keyPresses[key].duration == 0;
}


unsigned int Input::getRawKeyDownDuration(RawKeyboardKey key) {
	return keyPresses[key].duration;
}


bool Input::getRawMouseButton(RawMouseButton key) {
	return mouseButtonPresses[key].occurring;
}


bool Input::getRawMouseButtonTapped(RawMouseButton key) {
	return mouseButtonPresses[key].occurring && mouseButtonPresses[key].duration == 0;
}


unsigned int Input::getRawMouseButtonDownDuration(RawMouseButton key) {
	return mouseButtonPresses[key].duration;
}


bool Input::getRawControllerButton(RawControllerButton key) {
	return controllerButtonPresses[key].occurring;
}


bool Input::getRawControllerButtonTapped(RawControllerButton key) {
	return controllerButtonPresses[key].occurring && controllerButtonPresses[key].duration == 0;
}


unsigned int Input::getRawControllerButtonDownDuration(RawControllerButton key) {
	return controllerButtonPresses[key].duration;
}


void Input::processInput() {
	// Update key durations for all down keys
	for (unsigned int i = 0; i < NUM_KEYBOARDKEYS; ++i) {
		if (keyPresses[i].occurring)
			++keyPresses[i].duration;
	}
	//tappedKeys.clear();
	for (unsigned int i = 0; i < NUM_MOUSEBUTTONS; ++i) {
		if (mouseButtonPresses[i].occurring)
			++mouseButtonPresses[i].duration;
	}
	//tappedMouseButtons.clear();
	for (unsigned int i = 0; i < NUM_ACTIONS; ++i) {
		if (virtualController.actions[i].occurring)
			++virtualController.actions[i].duration;
	}
	//tappedActions.clear();

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

			// TODO add a case for controller connecting/disconnecting
		}
	}

	virtualController.movementAxes.set(virtualController.actions[ACTION_RIGHT].magnitude - virtualController.actions[ACTION_LEFT].magnitude,
									   virtualController.actions[ACTION_DOWN ].magnitude - virtualController.actions[ACTION_UP  ].magnitude);
}


void Input::handleMouseMotion(SDL_Event & e) {
	virtualController.usingKeyboard = true;

	virtualController.mousePos.set((float)e.motion.x, (float)e.motion.y);
}


void Input::handleKey(SDL_Event & e, bool down) {
	virtualController.usingKeyboard = true;

	// Raw keyboard input
	auto keyMap = SDL_KToRawKey.find(e.key.keysym.sym); // map sdl key to game key
	if (keyMap == SDL_KToRawKey.end())
		return;
	
	// Set the down status of the key, and clear the duration if key goes up
	RawKeyboardKey key = keyMap->second;
	keyPresses[key].occurring = down;
	keyPresses[key].duration = keyPresses[key].duration * down;

	//if (keyPresses[key].occurring && keyPresses[key].duration == 0)
	//	tappedKeys.push_back(key);


	// Game action mapping
	auto actionMap = RawKeyToAction.find(key); // map game key to game action
	if (actionMap == RawKeyToAction.end())
		return;

	// Set the occurring status of the action, and clear the duration if action ends
	Action action = actionMap->second;
	virtualController.actions[action].occurring = down;
	virtualController.actions[action].duration = virtualController.actions[action].duration * down;
	virtualController.actions[action].magnitude = 1.0f * down;
}


void Input::handleMouseButton(SDL_Event & e, bool down) {
	virtualController.usingKeyboard = true;

	// TODO i might need to set mouseX and mouseY from the sdl button.x and button.x in e

	// Raw mouse button input
	auto buttonMap = SDL_ButtonToRawMouseButton.find(e.button.button); // map sdl button to game button
	if (buttonMap == SDL_ButtonToRawMouseButton.end())
		return;

	// Set down status of the button, clear the duration if button goes up
	RawMouseButton mb = buttonMap->second;
	mouseButtonPresses[mb].occurring = down;
	mouseButtonPresses[mb].duration = mouseButtonPresses[mb].duration * down;

	//if (mouseButtonPresses[mb].occurring && mouseButtonPresses[mb].duration == 0)
	//	tappedMouseButtons.push_back(mb);


	// Game action mapping
	auto actionMap = RawMouseButtonToAction.find(mb);
	if (actionMap == RawMouseButtonToAction.end())
		return;

	// Set occurring status of the action, clear the duration if action ends
	Action action = actionMap->second;
	virtualController.actions[action].occurring = down;
	virtualController.actions[action].duration = virtualController.actions[action].duration * down;
	virtualController.actions[action].magnitude = 1.0f * down;
}


void Input::handleControllerAxisMotion(SDL_Event & e) {
	const float min = -32768;
	const float max = 32767;

	// Raw unsplit axis mapping
	auto axisMap = SDL_ControllerAxisToRawControllerAxis.find(e.caxis.axis);
	if (axisMap == SDL_ControllerAxisToRawControllerAxis.end())
		return;
	
	// Deadzone calculation
	float value = e.caxis.value / max;
	float absvalue = std::abs(value);

	if (absvalue < deadzone) {
		absvalue = 0.0f;
		if (virtualController.usingKeyboard)
			return; // return if using KB+M and controller was only nudged slightly
	}
	virtualController.usingKeyboard = false;

	absvalue = (absvalue - deadzone) / (1.0f - deadzone);
	absvalue = clamp(absvalue, 0.0f, 1.0f);
	value = std::copysignf(absvalue, value);

	// This is the most complicated part. We need to split up each positive and negative part
	// of each axis into a single 0.0 to 1.0 axis. This way we can assign +X and -X from the same
	// stick to their own actions. Complete remappability.
	UnsplitRawControllerAxis unsplitAxis = axisMap->second;
	RawControllerAxis splitAxes[2];
	int numAxes = 1;

	switch (unsplitAxis) {
		case USA_LSTICKX: {
			if (value > 0.0f) {
				splitAxes[0] = CA_LPOSX;
			}
			else if (value < 0.0f) {
				splitAxes[0] = CA_LNEGX;
			}
			else {
				splitAxes[0] = CA_LPOSX;
				splitAxes[1] = CA_LNEGX;
				numAxes = 2;
			}
		} break;

		case USA_LSTICKY: {
			if (value > 0.0f) {
				splitAxes[0] = CA_LPOSY;
			}
			else if (value < 0.0f) {
				splitAxes[0] = CA_LNEGY;
			}
			else {
				splitAxes[0] = CA_LPOSY;
				splitAxes[1] = CA_LNEGY;
				numAxes = 2;
			}
		} break;

		case USA_RSTICKX: {
			if (value > 0.0f) {
				splitAxes[0] = CA_RPOSX;
			}
			else if (value < 0.0f) {
				splitAxes[0] = CA_RNEGX;
			}
			else {
				splitAxes[0] = CA_RPOSX;
				splitAxes[1] = CA_RNEGX;
				numAxes = 2;
			}
		} break;

		case USA_RSTICKY: {
			if (value > 0.0f) {
				splitAxes[0] = CA_RPOSY;
			}
			else if (value < 0.0f) {
				splitAxes[0] = CA_RNEGY;
			}
			else {
				splitAxes[0] = CA_RPOSY;
				splitAxes[1] = CA_RNEGY;
				numAxes = 2;
			}
		} break;
	
		case USA_LTRIGGER: {
			splitAxes[0] = CA_LTRIGGER;
		} break;

		case USA_RTRIGGER: {
			splitAxes[0] = CA_RTRIGGER;
		} break;
	}

	// If 0 is received from controller, send action with magnitude of 0 to both actions associate with the axis
	for (int i = 0; i < numAxes; ++i) {
		auto actionMap = RawControllerAxisToAction.find(splitAxes[i]);
		if (actionMap != RawControllerAxisToAction.end()) {

			// Set occurring status of the action, clear the duration if action ends
			Action action = actionMap->second;
			bool occurring = value != 0.0f;

			virtualController.actions[action].occurring = occurring;
			virtualController.actions[action].duration = virtualController.actions[action].duration * occurring;
			virtualController.actions[action].magnitude = std::abs(value) * occurring;
		}
	}

	// TODO
}


void Input::handleControllerButton(SDL_Event & e, bool down) {
	virtualController.usingKeyboard = false;

	// Raw controller button input
	auto buttonMap = SDL_ControllerButtonToRawControllerButton.find(e.cbutton.button); // map sdl button to game button
	if (buttonMap == SDL_ControllerButtonToRawControllerButton.end())
		return;

	// Set down status of the button, clear the duration if button goes up
	RawControllerButton cb = buttonMap->second;
	mouseButtonPresses[cb].occurring = down;
	mouseButtonPresses[cb].duration = mouseButtonPresses[cb].duration * down;

	// TODO if I re-add lists of tapped buttons, I will need to fix these names
	//if (mouseButtonPresses[mb].occurring && mouseButtonPresses[mb].duration == 0)
	//	tappedMouseButtons.push_back(mb);

	// Game action mapping
	auto actionMap = RawControllerButtonToAction.find(cb);
	if (actionMap == RawControllerButtonToAction.end())
		return;

	// Set occurring status of the action, clear the duration if action ends
	Action action = actionMap->second;
	virtualController.actions[action].occurring = down;
	virtualController.actions[action].duration = virtualController.actions[action].duration * down;
	virtualController.actions[action].magnitude = 1.0f * down;
}