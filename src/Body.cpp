#include "Body.h"
#include "Game.h" // TODO remove this
#include "Entity.h"

Body::Body() {
    executionOrder = 0;
}

Body::~Body() {

}

void Body::init() {

}

void Body::destroy() {

}

void Body::pretick() {
	if (useGravity)
		acc = gravity;

	vel = vel + acc;

	if (auto entityLock = entity.lock()) {
		entityLock->localPos = entityLock->localPos + vel;

		if (Game::input->getAction(Input::Action::ACTION_JUMP))
			entityLock->localPos = Game::input->getMousePos() / Game::renderer->camera.zoom;
	}

	
	// TODO this is most certainly in the wrong place
	// Apply drag
	// vel.set(moveTo(vel.xf(), 0.0f, drag.xf()), moveTo(vel.yf(), 0.0f, drag.yf()));
}

void Body::tick() {
	if (entity.lock() && randomNum() > 0.9f) {
		// Game::logger << "we jigglin\n";
		vel.addX(randomNum(-1, 1));
		vel.addY(randomNum(-1, 1));
	}
}

void Body::posttick() {

}

// TODO needs more info, like size
// Vector Body::center() {
// 	Vector center;  
// 	if (auto entityLock = entity.lock()) {
// 		center = center + entityLock->pos;
// 	}
// 	return center + aabb / 2.0f;
// }