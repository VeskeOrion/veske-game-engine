//----------------------------------------------------------------------------------------//
// Main.cpp
// The entry point for a game.
//----------------------------------------------------------------------------------------//


#include <SDL/SDL.h>
#include <GL/glew.h>
#include "GameEngine.h"


int main(int argc, char** argv) {
	GameEngine engine;

	engine.start();

	return 0;
}