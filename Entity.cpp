#include "Entity.h"
#include "Game.h"

unsigned int Entity::entityIDCounter = 0;


Entity::Entity() {
	entityID = entityIDCounter;
	entityIDCounter++;

	zIndex = 0;
	active = true;
	transparency = 1.0;

	// TODO remove this
	Game::logger << "Creating an entity." << "\n";
}


Entity::~Entity() {

}


void Entity::pretick() {
	pos.set((float)Game::input->mouseX, (float)Game::input->mouseY);
}


void Entity::tick() {

}


void Entity::posttick() {

}