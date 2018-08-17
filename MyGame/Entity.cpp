#include "Entity.h"
#include "Game.h"
#include "Terrain.h"


unsigned int Entity::entityIDCounter = 0;


Entity::Entity() {
	init();
}


Entity::~Entity() {
	// TODO set children positions and remove parent's child
	
	// TODO remove this
	Game::logger << "Destroying an entity.\n";
}


void Entity::init() {
	entityID = entityIDCounter;
	++entityIDCounter;

	name = "Entity" + std::to_string(entityID);

	active = true;
	useGravity = false;

	zIndex = 0;
	visible = true;
	alpha = 1.0;

	// TODO remove this
	Game::logger << "Creating an entity.\n";
}


void Entity::integrate() {
	Vector lastPos = pos;

	// Move body so drag doesn't affect velocities that were applied just last frame
	if (useGravity)
		acc.setY(0.1f);

	vel = vel + acc;
	pos = pos + vel;

	if (withinEpsilon(pos.xf(), lastPos.xf()))
		vel.setX(0.0f);
	if (withinEpsilon(pos.yf(), lastPos.yf()))
		vel.setY(0.0f);
	
	// Apply drag
	vel.set(moveTo(vel.xf(), 0.0f, drag.xf()), moveTo(vel.yf(), 0.0f, drag.yf()));


}


void Entity::handleCollisions() {
	for (auto i : collisionList) {

		// Collision with terrain
		if (std::shared_ptr<Terrain> t = std::dynamic_pointer_cast<Terrain>(i)) {
			////int entityMidpoint = (pos.x() + size.x()) / 2;
			//int xCoordThatRestsUponTerrain = pos.x() + size.x();
			//int heightmapIndex = (xCoordThatRestsUponTerrain - t->pos.x()) / t->resolution;
			//if (0 <= heightmapIndex && heightmapIndex < t->heightMap.size()) {
			//	int height = t->heightMap[heightmapIndex];
			//	pos.setY(t->pos.y() + t->size.y() - height - size.y());
			//}
		}

		// Collision with regular entity
		else {
			switch (collisionType) {
				case KINEMATIC: {
					// do nothing
				} break;

				case STRONG: {
					
				} break;

				case WEAK: {

				} break;

				case TRIGGER: {

				} break;

				case NONE: {

				} break;
			}
		}
	}
}


void Entity::pretick() {

}


void Entity::tick() {
	// Update animation frame // TODO should this be at the end of tick?
	sprite.currentAnim.update();
	//pos = Game::input->getMousePos() / (int)Game::renderer->scaleFactor;
}


void Entity::posttick() {
	// TODO maybe put this back some day collisionList.clear();
}


void Entity::destroy() {
	Game::world->removeEntity(thisEntity.lock());
}


bool Entity::checkCollision(std::shared_ptr<Entity> e) {
	bool xcontains = (pos.x()    <= e->pos.x() && e->pos.x() < pos.x()    + size.x()   ) ||
					 (e->pos.x() <= pos.x()    && pos.x()    < e->pos.x() + e->size.x());
	bool ycontains = (pos.y()    <= e->pos.y() && e->pos.y() < pos.y()    + size.y()   ) ||
					 (e->pos.y() <= pos.y()    && pos.y()    < e->pos.y() + e->size.y());

	return xcontains && ycontains;
}