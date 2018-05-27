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
	// Move body so drag doesn't affect velocities that were applied just last frame
	vel = vel + acc;
	pos = pos + vel;
	
	// Apply drag
	vel.set(moveTo(vel.xf(), 0.0f, drag.xf()), moveTo(vel.yf(), 0.0f, drag.yf()));

	// Update animation frame // TODO should this be at the end of tick?
	sprite.currentAnim.update();
}


void Entity::tick() {
	//pos = Game::input->getMousePos() / (int)Game::renderer->scaleFactor;
}


void Entity::posttick() {

}


void Entity::kill() {
	Game::world->removeEntity(this);
}