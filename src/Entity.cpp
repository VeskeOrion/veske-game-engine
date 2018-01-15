#include "Entity.h"
#include "Game.h"

unsigned int Entity::entityIDCounter = 0;


Entity::Entity() {
	entityID = entityIDCounter;
	entityIDCounter++;

	zIndex = 0;
	active = true;
	visible = true;

	// TODO remove this
	Game::logger << "Creating an entity." << "\n";
}


Entity::~Entity() {

}


void Entity::pretick() {

}


void Entity::tick() {
	pos.add(2, 1);
}


void Entity::posttick() {

}