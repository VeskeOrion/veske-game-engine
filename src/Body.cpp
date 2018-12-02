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

	// Move body so drag doesn't affect velocities that were applied just last frame
	if (useGravity)
		acc = gravity;

	vel = vel + acc;

	if (auto entityLock = entity.lock()) {
		entityLock->pos = entityLock->pos + vel;

		if (Game::input->getAction(Input::Action::ACTION_JUMP))
			entityLock->pos = Game::input->getMousePos() / Game::renderer->camera.zoom;
	}

	// why? TODO?
	// if (withinEpsilon(pos.xf(), lastPos.xf()))
	// 	vel.setX(0.0f);
	// if (withinEpsilon(pos.yf(), lastPos.yf()))
	// 	vel.setY(0.0f);
	
	// TODO this is mos certainly in the wrong place
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