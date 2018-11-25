#include "Body.h"

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
}

void Body::tick() {

}

void Body::posttick() {

}