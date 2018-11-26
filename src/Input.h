//----------------------------------------------------------------------------------------//
// Input.h
// Contains a class that manages all keyboard input. Keypresses and information about them
// are stored in the keypresses array. The values in this array are updated one per frame.
// Access this class via Game::input.
//----------------------------------------------------------------------------------------//


#ifndef INPUT_H
#define INPUT_H


#include <list>
#include <map>
#include <array>

#include <SDL.h>

#include "Math.h"


#define KEY_DOWN true
#define KEY_UP false




class Input {
public:

	// Codes for all raw keyboard keys
	enum RawKeyboardKey {
		K_A, K_B, K_C, K_D, K_E, K_F, K_G, K_H, K_I, K_J, K_K, K_L, K_M, K_N, K_O, K_P, K_Q, K_R, K_S, K_T, K_U, K_V, K_W, K_X, K_Y, K_Z,
		K_ZERO, K_ONE, K_TWO, K_THREE, K_FOUR, K_FIVE, K_SIX, K_SEVEN, K_EIGHT, K_NINE,
		K_BACKSPACE, K_TAB, K_RETURN, K_ESCAPE, K_SPACE, K_DELETE,
		K_ARROWUP, K_ARROWDOWN, K_ARROWLEFT, K_ARROWRIGHT,
		K_INSERT, K_HOME, K_END, K_PAGEUP, K_PAGEDOWN, /*K_NUMLOCK,*/ K_CAPSLOCK, K_SCROLLLOCK,
		K_RSHIFT, K_LSHIFT, K_RCTRL, K_LCTRL, K_RALT, K_LALT,
		K_QUOTE, K_COMMA, K_MINUS, K_PERIOD, K_SLASH, K_SEMICOLON, K_EQUALS, K_LEFTBRACKET, K_BACKSLASH, K_RIGHTBRACKET, K_TILDE,
		K_NUMZERO, K_NUMONE, K_NUMTWO, K_NUMTHREE, K_NUMFOUR, K_NUMFIVE, K_NUMSIX, K_NUMSEVEN, K_NUMEIGHT, K_NUMNINE,
		K_NUMPERIOD, K_NUMDIVIDE, K_NUMMULTIPLY, K_NUMMINUS, K_NUMPLUS, K_NUMENTER,
		K_F1, K_F2, K_F3, K_F4, K_F5, K_F6, K_F7, K_F8, K_F9, K_F10, K_F11, K_F12,
		NUM_KEYBOARDKEYS
	};

	// Codes for all raw mouse buttons
	enum RawMouseButton {
		MB_MOUSELEFT, MB_MOUSERIGHT, MB_MOUSEMIDDLE, NUM_MOUSEBUTTONS
	};

	// Codes for all raw controller axes
	enum UnsplitRawControllerAxis {
		USA_LSTICKX, USA_LSTICKY, USA_RSTICKX, USA_RSTICKY,
		USA_LTRIGGER, USA_RTRIGGER,
		NUM_UNSPLITECONTROLLERAXES
	};
	enum RawControllerAxis {
		CA_LNEGX, CA_LPOSX, CA_LPOSY, CA_LNEGY,
		CA_RNEGX, CA_RPOSX, CA_RPOSY, CA_RNEGY,
		CA_LTRIGGER, CA_RTRIGGER,
		NUM_CONTROLLERAXES
	};

	// Codes for all raw gamepad buttons
	enum RawControllerButton {
		CB_A, CB_B, CB_X, CB_Y,
		CB_START, CB_SELECT,
		CB_LBUMPER, CB_RBUMPER, /*CB_LTRIGGER, CB_RTRIGGER,*/
		CB_LSTICK, CB_RSTICK,
		CB_UP, CB_DOWN, CB_LEFT, CB_RIGHT,
		NUM_CONTROLLERBUTTONS
	};

	// Codes for all mappable actions
	enum Action {
		ACTION_LEFT, ACTION_RIGHT, ACTION_DOWN, ACTION_UP,
		ACTION_RUN, ACTION_CROUCH, ACTION_JUMP,
		ACTION_ATTACK_PRIMARY, ACTION_ATTACK_SECONDARY, ACTION_ACTIVATE,
		ACTION_MENU,
		NUM_ACTIONS
	};

	// An instance of an input from the player
	struct InputPacket {
		bool occurring;
		unsigned int duration;
		float magnitude;
	};

	// SDL -> Raw Key
	const std::map<int, RawKeyboardKey> SDL_KToRawKey {
		{ SDLK_a, K_A },
		{ SDLK_b, K_B },
		{ SDLK_c, K_C },
		{ SDLK_d, K_D },
		{ SDLK_e, K_E },
		{ SDLK_f, K_F },
		{ SDLK_g, K_G },
		{ SDLK_h, K_H },
		{ SDLK_i, K_I },
		{ SDLK_j, K_J },
		{ SDLK_k, K_K },
		{ SDLK_l, K_L },
		{ SDLK_m, K_M },
		{ SDLK_n, K_N },
		{ SDLK_o, K_O },
		{ SDLK_p, K_P },
		{ SDLK_q, K_Q },
		{ SDLK_r, K_R },
		{ SDLK_s, K_S },
		{ SDLK_t, K_T },
		{ SDLK_u, K_U },
		{ SDLK_v, K_V },
		{ SDLK_w, K_W },
		{ SDLK_x, K_X },
		{ SDLK_y, K_Y },
		{ SDLK_z, K_Z },
		{ SDLK_0, K_ZERO },
		{ SDLK_1, K_ONE },
		{ SDLK_2, K_TWO },
		{ SDLK_3, K_THREE },
		{ SDLK_4, K_FOUR },
		{ SDLK_5, K_FIVE },
		{ SDLK_6, K_SIX },
		{ SDLK_7, K_SEVEN },
		{ SDLK_8, K_EIGHT },
		{ SDLK_9, K_NINE },
		{ SDLK_BACKSPACE, K_BACKSPACE },
		{ SDLK_TAB, K_TAB },
		{ SDLK_RETURN, K_RETURN },
		{ SDLK_ESCAPE, K_ESCAPE },
		{ SDLK_SPACE, K_SPACE },
		{ SDLK_DELETE, K_DELETE },
		{ SDLK_UP, K_ARROWUP },
		{ SDLK_DOWN, K_ARROWDOWN },
		{ SDLK_LEFT, K_ARROWLEFT },
		{ SDLK_RIGHT, K_ARROWRIGHT },
		{ SDLK_INSERT, K_INSERT },
		{ SDLK_HOME, K_HOME },
		{ SDLK_END, K_END },
		{ SDLK_PAGEUP, K_PAGEUP },
		{ SDLK_PAGEDOWN, K_PAGEDOWN },
		/*{ SDLK_LOCK, K_NUMLOCK },*/ // no SDLK_NUMLOCK
		{ SDLK_CAPSLOCK, K_CAPSLOCK },
		{ SDLK_SCROLLLOCK, K_SCROLLLOCK },
		{ SDLK_RSHIFT, K_RSHIFT },
		{ SDLK_LSHIFT, K_LSHIFT },
		{ SDLK_RCTRL, K_RCTRL },
		{ SDLK_LCTRL, K_LCTRL },
		{ SDLK_RALT, K_RALT },
		{ SDLK_LALT, K_LALT },
		{ SDLK_QUOTE, K_QUOTE },
		{ SDLK_COMMA, K_COMMA },
		{ SDLK_MINUS, K_MINUS },
		{ SDLK_PERIOD, K_PERIOD },
		{ SDLK_SLASH, K_SLASH },
		{ SDLK_SEMICOLON, K_SEMICOLON },
		{ SDLK_EQUALS, K_EQUALS },
		{ SDLK_LEFTBRACKET, K_LEFTBRACKET },
		{ SDLK_BACKSLASH, K_BACKSLASH },
		{ SDLK_RIGHTBRACKET, K_RIGHTBRACKET },
		{ SDLK_BACKQUOTE, K_TILDE },
		{ SDLK_KP_0, K_NUMZERO },
		{ SDLK_KP_1, K_NUMONE },
		{ SDLK_KP_2, K_NUMTWO },
		{ SDLK_KP_3, K_NUMTHREE },
		{ SDLK_KP_4, K_NUMFOUR },
		{ SDLK_KP_5, K_NUMFIVE },
		{ SDLK_KP_6, K_NUMSIX },
		{ SDLK_KP_7, K_NUMSEVEN },
		{ SDLK_KP_8, K_NUMEIGHT },
		{ SDLK_KP_9, K_NUMNINE },
		{ SDLK_KP_PERIOD, K_NUMPERIOD },
		{ SDLK_KP_DIVIDE, K_NUMDIVIDE },
		{ SDLK_KP_MULTIPLY, K_NUMMULTIPLY },
		{ SDLK_KP_MINUS, K_NUMMINUS },
		{ SDLK_KP_PLUS, K_NUMPLUS },
		{ SDLK_KP_ENTER, K_NUMENTER },
		{ SDLK_F1, K_F1 },
		{ SDLK_F2, K_F2 },
		{ SDLK_F3, K_F3 },
		{ SDLK_F4, K_F4 },
		{ SDLK_F5, K_F5 },
		{ SDLK_F6, K_F6 },
		{ SDLK_F7, K_F7 },
		{ SDLK_F8, K_F8 },
		{ SDLK_F9, K_F9 },
		{ SDLK_F10, K_F10 },
		{ SDLK_F11, K_F11 },
		{ SDLK_F12, K_F12 }
	};

	// SDL -> Raw Mouse Button
	const std::map<int, RawMouseButton> SDL_ButtonToRawMouseButton {
		{ SDL_BUTTON_LEFT, MB_MOUSELEFT },
		{ SDL_BUTTON_RIGHT, MB_MOUSERIGHT },
		{ SDL_BUTTON_MIDDLE, MB_MOUSEMIDDLE }
	};

	// SDL -> Raw Controller Axis
	const std::map<int, UnsplitRawControllerAxis> SDL_ControllerAxisToRawControllerAxis {
		{ SDL_CONTROLLER_AXIS_LEFTX, USA_LSTICKX },
		{ SDL_CONTROLLER_AXIS_LEFTY, USA_LSTICKY },
		{ SDL_CONTROLLER_AXIS_TRIGGERLEFT, USA_LTRIGGER },
		{ SDL_CONTROLLER_AXIS_TRIGGERRIGHT, USA_RTRIGGER },
	};

	// SDL -> Raw Controller Button
	const std::map<int, RawControllerButton> SDL_ControllerButtonToRawControllerButton {
		{ SDL_CONTROLLER_BUTTON_A, CB_A },
		{ SDL_CONTROLLER_BUTTON_B, CB_B },
		{ SDL_CONTROLLER_BUTTON_X, CB_X },
		{ SDL_CONTROLLER_BUTTON_Y, CB_Y },
		{ SDL_CONTROLLER_BUTTON_BACK, CB_SELECT },
		{ SDL_CONTROLLER_BUTTON_START, CB_START },
		{ SDL_CONTROLLER_BUTTON_LEFTSHOULDER, CB_LBUMPER },
		{ SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, CB_RBUMPER },
		{ SDL_CONTROLLER_BUTTON_LEFTSTICK , CB_LSTICK },
		{ SDL_CONTROLLER_BUTTON_RIGHTSTICK , CB_RSTICK },
		{ SDL_CONTROLLER_BUTTON_DPAD_UP , CB_UP },
		{ SDL_CONTROLLER_BUTTON_DPAD_DOWN , CB_DOWN },
		{ SDL_CONTROLLER_BUTTON_DPAD_LEFT , CB_LEFT },
		{ SDL_CONTROLLER_BUTTON_DPAD_RIGHT , CB_RIGHT },
	};


	// Default key mappings
	std::map<RawKeyboardKey, Action> RawKeyToAction {
		{ K_W, ACTION_UP },
		{ K_A, ACTION_LEFT },
		{ K_S, ACTION_DOWN },
		{ K_D, ACTION_RIGHT },
		{ K_LSHIFT, ACTION_RUN },
		{ K_LCTRL, ACTION_CROUCH },
		{ K_SPACE, ACTION_JUMP },
		{ K_E, ACTION_ACTIVATE },
		{ K_TAB, ACTION_MENU }
	};

	// Default mouse button mappings
	std::map<RawMouseButton, Action> RawMouseButtonToAction {
		{ MB_MOUSELEFT, ACTION_ATTACK_PRIMARY },
		{ MB_MOUSERIGHT, ACTION_ATTACK_SECONDARY }
	};

	// Default controller axis mappings
	std::map<RawControllerAxis, Action> RawControllerAxisToAction {
		{ CA_LNEGX, ACTION_LEFT },
		{ CA_LPOSX, ACTION_RIGHT },
		{ CA_LNEGY, ACTION_UP },
		{ CA_LPOSY, ACTION_DOWN },
		{ CA_LTRIGGER, ACTION_CROUCH },
		{ CA_RTRIGGER, ACTION_RUN }
	};

	// Default controller button mappings // TODO actually set these to defaults
	std::map<RawControllerButton, Action> RawControllerButtonToAction {
		{ CB_A, ACTION_RUN },
		{ CB_X, ACTION_ATTACK_PRIMARY },
		{ CB_Y, ACTION_ATTACK_SECONDARY },
		{ CB_LBUMPER, ACTION_CROUCH }
	};


	// Behold, our master "virtual controller", the authoritative state of all mapped inputs
	struct {
		bool usingKeyboard; // if the last input was keyboard (can change UI based on this)

		Vector mousePos;
		Vector movementAxes; // horizontal and vertical movement axes

		InputPacket actions[NUM_ACTIONS]; // all actions
	} virtualController;


	InputPacket mouseButtonPresses[NUM_MOUSEBUTTONS];
	InputPacket keyPresses[NUM_KEYBOARDKEYS];
	InputPacket controllerButtonPresses[NUM_CONTROLLERBUTTONS];
	InputPacket controllerAxisMovement[NUM_CONTROLLERAXES];

	//std::list<Action> tappedActions;
	//std::list<RawKeyboardKey> tappedKeys;
	//std::list<RawMouseButton> tappedMouseButtons;

	SDL_GameController * controller = nullptr; // optional SDL game controller handle
	float deadzone = 0.15f;

	Input();
	~Input();

	// The five most important input functions, get the state of the virtual controller
	Vector getMousePos();
	Vector getMovementAxes();
	bool getAction(Action action);
	bool getActionTapped(Action action);
	unsigned int getActionDuration(Action action);

	// Raw key getters
	bool getRawKey(RawKeyboardKey key);
	bool getRawKeyTapped(RawKeyboardKey key);
	unsigned int getRawKeyDownDuration(RawKeyboardKey key);

	// Raw mouse button getters
	bool getRawMouseButton(RawMouseButton key);
	bool getRawMouseButtonTapped(RawMouseButton key);
	unsigned int getRawMouseButtonDownDuration(RawMouseButton key);

	// Raw controller getters
	bool getRawControllerButton(RawControllerButton key);
	bool getRawControllerButtonTapped(RawControllerButton key);
	unsigned int getRawControllerButtonDownDuration(RawControllerButton key);

	// Internal input processing functions
	bool init();
	void processInput();
	void handleMouseMotion(SDL_Event & e);
	void handleKey(SDL_Event & e, bool down);
	void handleMouseButton(SDL_Event & e, bool down);
	void handleControllerAxisMotion(SDL_Event & e);
	void handleControllerButton(SDL_Event & e, bool down);
};


#endif // INPUT_H