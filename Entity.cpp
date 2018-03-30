#include "Entity.h"
#include "Game.h"


unsigned int Entity::entityIDCounter = 0;


Entity::Entity() {
	entityID = entityIDCounter;
	++entityIDCounter;

	zIndex = 0;
	visible = true;
	alpha = 1.0;

	active = true;

	// TODO remove this
	Game::logger << "Creating an entity.\n";
}


Entity::~Entity() {
	// TODO set children positions and remove parent's child
	Game::logger << "Destroying an entity.\n";
}

void Entity::pretick() {
	// TODO make this detect collisions and not just move primitively
	pos = pos + vel;
	vel = vel + acc; // TODO decide if vel should be increase before or after pos
	
	// TODO apply drag
}


void Entity::tick() {
	sprite.currentAnim.update();
}


void Entity::posttick() {

}


void Entity::kill() {
	Game::world->removeEntity(this);
}