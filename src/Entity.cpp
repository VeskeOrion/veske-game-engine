#include "Entity.h"
#include "Game.h"
#include "Terrain.h"
#include "Component.h"


unsigned int Entity::entityIDCounter = 0;


Entity::Entity() {
	init();
}


Entity::~Entity() {
	// TODO set children positions and remove parent's child
	
	// TODO remove this
	// Game::logger << "Destroying an entity.\n";
}


void Entity::init() {
	entityID = entityIDCounter;
	++entityIDCounter;

	name = "Entity" + std::to_string(entityID);

	active = true;
	// useGravity = false;

	// zIndex = 0;
	// visible = true;
	// alpha = 1.0;

	// TODO remove this
	// Game::logger << "Creating an entity.\n";

	// TODO decide how to init components
	// for (std::shared_ptr<Component> com : components) {
	// 	com->init();
	// }
}


void Entity::pretick() {


	for (std::shared_ptr<Component> com : components) {
		com->pretick();
	}
}


void Entity::tick() {
	// Update animation frame // TODO should this be at the end of tick?
	//sprite.currentAnim.update();
	//pos = Game::input->getMousePos() / (int)Game::renderer->scaleFactor;

	for (std::shared_ptr<Component> com : components) {
		com->tick();
	}
}


void Entity::posttick() {

	for (std::shared_ptr<Component> com : components) {
		com->posttick();
	}
}


void Entity::destroy() {
	Game::world->removeEntity(thisEntity.lock());

	// TODO decide how to detroy components
	// for (std::shared_ptr<Component> com : components) {
	// 	com->init();
	// }
}





// bool Entity::checkCollision(std::shared_ptr<Entity> e) {
// 	bool xcontains = (pos.x()    <= e->pos.x() && e->pos.x() < pos.x()    + size.x()   ) ||
// 					 (e->pos.x() <= pos.x()    && pos.x()    < e->pos.x() + e->size.x());
// 	bool ycontains = (pos.y()    <= e->pos.y() && e->pos.y() < pos.y()    + size.y()   ) ||
// 					 (e->pos.y() <= pos.y()    && pos.y()    < e->pos.y() + e->size.y());

// 	return xcontains && ycontains;
// }