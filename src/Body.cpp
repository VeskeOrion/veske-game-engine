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
    // Vector lastPos = pos;

	// // Move body so drag doesn't affect velocities that were applied just last frame
	// if (useGravity)
	// 	acc.setY(0.1f);

	// vel = vel + acc;
	// pos = pos + vel;

	// if (withinEpsilon(pos.xf(), lastPos.xf()))
	// 	vel.setX(0.0f);
	// if (withinEpsilon(pos.yf(), lastPos.yf()))
	// 	vel.setY(0.0f);
	
	// // Apply drag
	// vel.set(moveTo(vel.xf(), 0.0f, drag.xf()), moveTo(vel.yf(), 0.0f, drag.yf()));
	if (auto entityLock = entity.lock()) {
		Game::logger << "we jigglin\n";
		entityLock->pos.addX(randomNum(-1, 1));
		entityLock->pos.addY(randomNum(-1, 1));
	}
}

void Body::tick() {

}

void Body::posttick() {

}