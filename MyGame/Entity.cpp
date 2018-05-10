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
	
	// Now apply drag
	//float newX = 0.0f;
	//float newY = 0.0f;

	//if (vel.xf() > 0.0f)
	//	newX = (vel.xf() - drag.xf() > 0.0f)? vel.xf() - drag.xf() : 0.0f;
	//else if (vel.x() < 0.0f)
	//	newX = (vel.xf() + drag.xf() < 0.0f)? vel.xf() + drag.xf() : 0.0f;

	//if (vel.y() > 0.0f)
	//	newY = (vel.yf() - drag.yf() > 0.0f)? vel.yf() - drag.yf() : 0.0f;
	//else if (vel.y() < 0.0f)
	//	newY = (vel.yf() + drag.yf() < 0.0f)? vel.yf() + drag.yf() : 0.0f;

	vel.set(moveTo(vel.xf(), 0.0f, drag.xf()), moveTo(vel.yf(), 0.0f, drag.yf()));

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