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

#include <SDL/SDL.h>

#include "Math.h"


#define KEY_DOWN true
#define KEY_UP false


class Input {
public:
	//struct InputPacket {
	//	enum Source {BUTTON, MOUSE, JOYSTICK};

	//	Source src;

	//	union {
	//		// Toggleable buttons
	//		struct {
	//			Button button;
	//			bool down;
	//			unsigned int duration;
	//		};

	//		// Mouse coordinates
	//		struct {
	//			int x;
	//			int y;
	//		};
	//		
	//		// Joystick offsets and ID
	//		struct {

	//		};
	//	};
	//};

	struct Press {
		bool down;
		unsigned int duration;
	};

	enum RawKey {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
		BACKSPACE, TAB, RETURN, ESCAPE, SPACE, DELETE,
		ARROWUP, ARROWDOWN, ARROWLEFT, ARROWRIGHT,
		INSERT, HOME, END, PAGEUP, PAGEDOWN, /*NUMLOCK,*/ CAPSLOCK, SCROLLLOCK,
		RSHIFT, LSHIFT, RCTRL, LCTRL, RALT, LALT,
		QUOTE, COMMA, MINUS, PERIOD, SLASH, SEMICOLON, EQUALS, LEFTBRACKET, BACKSLASH, RIGHTBRACKET, TILDE,
		NUMZERO, NUMONE, NUMTWO, NUMTHREE, NUMFOUR, NUMFIVE, NUMSIX, NUMSEVEN, NUMEIGHT, NUMNINE,
		NUMPERIOD, NUMDIVIDE, NUMMULTIPLY, NUMMINUS, NUMPLUS, NUMENTER,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		NUM_KEYS
	};
	const std::map<int, RawKey> SDL_KToRawKey {
		{ SDLK_a, A },
		{ SDLK_b, B },
		{ SDLK_c, C },
		{ SDLK_d, D },
		{ SDLK_e, E },
		{ SDLK_f, F },
		{ SDLK_g, G },
		{ SDLK_h, H },
		{ SDLK_i, I },
		{ SDLK_j, J },
		{ SDLK_k, K },
		{ SDLK_l, L },
		{ SDLK_m, M },
		{ SDLK_n, N },
		{ SDLK_o, O },
		{ SDLK_p, P },
		{ SDLK_q, Q },
		{ SDLK_r, R },
		{ SDLK_s, S },
		{ SDLK_t, T },
		{ SDLK_u, U },
		{ SDLK_v, V },
		{ SDLK_w, W },
		{ SDLK_x, X },
		{ SDLK_y, Y },
		{ SDLK_z, Z },
		{ SDLK_0, ZERO },
		{ SDLK_1, ONE },
		{ SDLK_2, TWO },
		{ SDLK_3, THREE },
		{ SDLK_4, FOUR },
		{ SDLK_5, FIVE },
		{ SDLK_6, SIX },
		{ SDLK_7, SEVEN },
		{ SDLK_8, EIGHT },
		{ SDLK_9, NINE },
		{ SDLK_BACKSPACE, BACKSPACE },
		{ SDLK_TAB, TAB },
		{ SDLK_RETURN, RETURN },
		{ SDLK_ESCAPE, ESCAPE },
		{ SDLK_SPACE, SPACE },
		{ SDLK_DELETE, DELETE },
		{ SDLK_UP, ARROWUP },
		{ SDLK_DOWN, ARROWDOWN },
		{ SDLK_LEFT, ARROWLEFT },
		{ SDLK_RIGHT, ARROWRIGHT },
		{ SDLK_INSERT, INSERT },
		{ SDLK_HOME, HOME },
		{ SDLK_END, END },
		{ SDLK_PAGEUP, PAGEUP },
		{ SDLK_PAGEDOWN, PAGEDOWN },
		/*{ SDLK_LOCK, NUMLOCK },*/ // no SDLK_NUMLOCK
		{ SDLK_CAPSLOCK, CAPSLOCK },
		{ SDLK_SCROLLLOCK, SCROLLLOCK },
		{ SDLK_RSHIFT, RSHIFT },
		{ SDLK_LSHIFT, LSHIFT },
		{ SDLK_RCTRL, RCTRL },
		{ SDLK_LCTRL, LCTRL },
		{ SDLK_RALT, RALT },
		{ SDLK_LALT, LALT },
		{ SDLK_QUOTE, QUOTE },
		{ SDLK_COMMA, COMMA },
		{ SDLK_MINUS, MINUS },
		{ SDLK_PERIOD, PERIOD },
		{ SDLK_SLASH, SLASH },
		{ SDLK_SEMICOLON, SEMICOLON },
		{ SDLK_EQUALS, EQUALS },
		{ SDLK_LEFTBRACKET, LEFTBRACKET },
		{ SDLK_BACKSLASH, BACKSLASH },
		{ SDLK_RIGHTBRACKET, RIGHTBRACKET },
		{ SDLK_BACKQUOTE, TILDE },
		{ SDLK_KP_0, NUMZERO },
		{ SDLK_KP_1, NUMONE },
		{ SDLK_KP_2, NUMTWO },
		{ SDLK_KP_3, NUMTHREE },
		{ SDLK_KP_4, NUMFOUR },
		{ SDLK_KP_5, NUMFIVE },
		{ SDLK_KP_6, NUMSIX },
		{ SDLK_KP_7, NUMSEVEN },
		{ SDLK_KP_8, NUMEIGHT },
		{ SDLK_KP_9, NUMNINE },
		{ SDLK_KP_PERIOD, NUMPERIOD },
		{ SDLK_KP_DIVIDE, NUMDIVIDE },
		{ SDLK_KP_MULTIPLY, NUMMULTIPLY },
		{ SDLK_KP_MINUS, NUMMINUS },
		{ SDLK_KP_PLUS, NUMPLUS },
		{ SDLK_KP_ENTER, NUMENTER },
		{ SDLK_F1, F1 },
		{ SDLK_F2, F2 },
		{ SDLK_F3, F3 },
		{ SDLK_F4, F4 },
		{ SDLK_F5, F5 },
		{ SDLK_F6, F6 },
		{ SDLK_F7, F7 },
		{ SDLK_F8, F8 },
		{ SDLK_F9, F9 },
		{ SDLK_F10, F10 },
		{ SDLK_F11, F11 },
		{ SDLK_F12, F12 }
	};

	enum RawMouseButton {
		MOUSELEFT, MOUSERIGHT, MOUSEMIDDLE, NUM_MOUSEBUTTONS
	};
	const std::map<int, RawMouseButton> SDL_ButtonToRawMouseButton {
		{ SDL_BUTTON_LEFT, MOUSELEFT },
		{ SDL_BUTTON_RIGHT, MOUSERIGHT },
		{ SDL_BUTTON_MIDDLE, MOUSEMIDDLE }
	};

	// TODO add controller button support
	//enum RawControllerButton {
	//	C_A, C_B, C_X, C_Y, C_START, C_SELECT, C_RBUMPER, C_LBUMPER, LEFTSTICK, C_RIGHTSTICK
	//};

	enum InputMapping {
		LEFT, RIGHT, DOWN, UP, RUN, CROUCH, JUMP,
		ATTACK_PRIMARY, ATTACK_SECONDARY, ACTIVATE, MENU, NUM_ACTIONS
	};
	struct Action {
		bool occurring;
		unsigned int duration;
		float magnitude;
	};

	std::map<RawKey, InputMapping> RawKeyToAction {
		{ RawKey::W, UP },
		{ RawKey::A, LEFT },
		{ RawKey::S, DOWN },
		{ RawKey::D, RIGHT },
		{ RawKey::LSHIFT, RUN },
		{ RawKey::LCTRL, CROUCH },
		{ RawKey::SPACE, JUMP },
		{ RawKey::E, ACTIVATE },
		{ RawKey::TAB, MENU }
	};
	std::map<RawMouseButton, InputMapping> RawMouseButtonToAction {
		{ RawMouseButton::MOUSELEFT, ATTACK_PRIMARY },
		{ RawMouseButton::MOUSERIGHT, ATTACK_SECONDARY }
	};

	Input();
	~Input();

	Action actions[NUM_ACTIONS];
	std::list<InputMapping> tappedActions;

	Press keyPresses[NUM_KEYS];
	std::list<RawKey> tappedKeys;

	Press mouseButtonPresses[NUM_MOUSEBUTTONS];
	std::list<RawMouseButton> tappedMouseButtons;

	Vector mousePos;
	Vector movementAxes;

	SDL_GameController * controller = nullptr; // optional game controller

	bool init();

	Vector getMousePos();
	Vector getMovementAxes();

	bool getAction(InputMapping action);
	bool getActionTapped(InputMapping action);
	unsigned int getActionDuration(InputMapping action);

	bool getRawKey(RawKey key);
	bool getRawKeyTapped(RawKey key);
	unsigned int getRawKeyDownDuration(RawKey key);

	void processInput();
	void handleMouseMotion(SDL_Event & e);
	void handleControllerAxisMotion(SDL_Event & e);
	void handleMouseButton(SDL_Event & e, bool down);
	void handleKey(SDL_Event & e, bool down);
	void Input::handleControllerButton(SDL_Event & e, bool down);
};


#endif // INPUT_H