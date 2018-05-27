#include "World.h"
#include "Game.h"

#include "Entity.h"
#include "Player.h" // TODO remove this, this is for debug testing by spawning players
#include "Collision.h"


World::World() {

}


World::~World() {

}


std::shared_ptr<Entity> World::addEntity(Entity * e) {
	std::shared_ptr<Entity> esp;
	if (findEntity(e) == nullptr) {
		esp.reset(e);
		esp->thisEntity = esp; // assigns the thisEntity pointer in the entity
		entities.push_back(esp);
	}

	return esp;
}


std::shared_ptr<Entity> World::findEntity(Entity * e) {
	std::shared_ptr<Entity> r = nullptr;
	for (auto i = entities.begin(); i != entities.end(); ++i) {
		if ((*i)->entityID == e->entityID)
			r = *i;
	}
	return r;
}


std::shared_ptr<Entity> World::findEntity(const std::string & name) {
	std::shared_ptr<Entity> r = nullptr;
	for (auto i = entities.begin(); i != entities.end(); ++i) {
		if ((*i)->name.compare(name) == 0)
			r = *i;
	}
	return r;
}


// Queues an entity deletion until the end of the update, when it is actually deleted
void World::removeEntity(Entity * e) {
	std::shared_ptr<Entity> r = findEntity(e);
	deadEntities.push_back(r);
}


void World::init() {
	//setLevel();
	//loadLevel();
	//initializeLevel();
	
	////**************************************************************************////
	// PUT DEBUG WORLD INITIALIZATION CODE HERE


	// TODO remove this hardcoded adding player, should be done from a Level object

	//p->sprite.loadFromFile("Character.png", 48, 48);
	//p->sprite.setAnim("fun");

	//p->sprite.addAnim("fun2", 0, false, {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3});
	//p->sprite.loadFromFile("Character.png", 48, 48);
	//Entity * e = new Entity();
	//e->pos.addX(100);
	//Game::world->addEntity(e);
	//e->name = "Entity";
	//e->sprite.loadFromFile("colorful.png", 64, 64);
	//e->sprite.addAnim("fun", 0, true, {0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0});
	//e->sprite.setAnim("fun");

	for (int i = 0; i < 20; ++i) {
		Entity * e = new Entity();
		std::shared_ptr<Entity> k = Game::world->addEntity(e);
			e->name = "";
			e->name = "Entity" + std::to_string(i);

		if (random() > 0.95f) {
			e->pos.addX(100);
			e->sprite.loadFromFile("colorful.png", 64, 64);
			e->size.set(64, 64);
			if (random() > 0.5f)
				e->sprite.addAnim("fun", 0, true, { 0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0 });
			else
				e->sprite.addAnim("fun", 0, true, { 0,1,1,2,2,2,2,2,3,3,2,2,2,3,2,1,0,0,1,1 });
			e->sprite.setAnim("fun");
		}
		else if (random() > 0.5f) {
			e->sprite.loadFromFile("Wheel.png", 8, 8);
			e->size.set(8, 8);
		}
		else {
			k->sprite.loadFromFile("Character.png", 48, 48);
			e->size.set(48, 48);
		}

		e->pos.set(random(-200.0f, 200.0f), random(-200.0f, 200.0f));
	}
	//Game::world->removeEntity(p.get());

	std::shared_ptr<Entity> p = Game::world->addEntity(new Player());
	p->name = "Player";
	p->drag.set(1.0f, 1.0f);
	p->sprite.loadFromFile("Colorful.png", 64, 64);
	p->size.set(64, 64);

	Terrain t;
	for (unsigned int i = 0; i < t.heightMap.size(); ++i) {
		Game::logger << t.heightMap.at(i);
	}


	// PUT DEBUG WORLD INITIALIZATION CODE HERE
	////**************************************************************************////
}


void World::run() {
	initializeGameTime();

	while (!done) { // TODO figure out what constitutes 'done'
		updateGameTime();

		if (readyToTick()) {
			tick();

			incrementTickCounter();
		}
		render();
	}
}


void World::tick() {
	processInput();
	
	// Move entities, integrate velocity
	for (auto & e : entities) {
		if (e->active) {
			e->pretick();
		}
	}

	// Detect collisions
	populateCollisionLists();

	// Apply game logic, react to collisions
	for (auto & e : entities) {
		if (e->active) {
			e->tick();
		}
	}

	// Anything post frame that needs to be done
	for (auto & e : entities) {
		if (e->active) {
			e->posttick();
		}
	}

	// Remove dead entities
	for (auto i : deadEntities) {
		entities.remove(i);
	}
	deadEntities.clear();

	////**************************************************************************////
	// PUT DEBUG WORLD LOOP CODE HERE

	if (Game::input->getAction(Input::Action::ACTION_CROUCH))
		Game::renderer->camera.zoom += 0.2f;

	if (Game::input->getAction(Input::Action::ACTION_RUN))
		Game::renderer->camera.zoom -= 0.2f;

	if (findEntity("Player")->collisionList.size() != 0) {
		Game::logger << findEntity("Player")->collisionList.size() << "cols: ";
		for (auto & e : findEntity("Player")->collisionList) {

			Game::logger << e->name << " ";
		}

		Game::logger << "\n";
	}


	//Game::renderer->camera.zoom += Game::input->getMovementAxes().yf() * 0.1;

	// TODO remove this, but if I have to put world testing things here
	//for (auto & k : Game::input->tappedKeys)
		//Game::logger << k << "\n";
	//Game::logger << findEntity("Player")->pos.xf() << " " << findEntity("Player")->pos.yf() << "\n";
	//
	//if (entities.size() > 0)
	//	entities.back()->kill();
	//Game::logger << random() << "\n";

	//Game::logger << e->sprite.currentAnim.elapsed;

	// PUT DEBUG WORLD LOOP CODE HERE
	////**************************************************************************////
}


void World::render() {
	Game::renderer->render();
}


void World::processInput() {
	Game::input->processInput();
}


void World::populateCollisionLists() {
	// TODO this should be a quad tree fast collision detection algorithm
	// TODO could create collision objects that each entity stores isntead of storing the entity
	for (auto i = entities.begin(); i != entities.end(); ++i) {
		(*i)->collisionList.clear();
		for (auto j = entities.begin(); j != entities.end(); ++j) {
			bool xcontains = ((*i)->pos.x() < (*j)->pos.x() && (*j)->pos.x() < (*i)->pos.x() + (*i)->size.x()) ||
							 ((*j)->pos.x() < (*i)->pos.x() && (*i)->pos.x() < (*j)->pos.x() + (*j)->size.x());
			bool ycontains = ((*i)->pos.y() < (*j)->pos.y() && (*j)->pos.y() < (*i)->pos.y() + (*i)->size.y()) ||
							 ((*j)->pos.y() < (*i)->pos.y() && (*i)->pos.y() < (*j)->pos.y() + (*j)->size.y());
			if (xcontains && ycontains) {
				(*i)->collisionList.push_back(*j);
			}
		}
	}
}


void World::initializeGameTime() {
	startTime = (SDL_GetPerformanceCounter() * 1000.0 / SDL_GetPerformanceFrequency());
	currentTime = (SDL_GetPerformanceCounter() * 1000.0 / SDL_GetPerformanceFrequency()) - startTime;
	timeOfLastTick = currentTime;
	gameTicks = 0;
	accumulator = 0.0;
	double fps = 60.0;
}


void World::updateGameTime() {
	double lastTime = currentTime;
	currentTime = (SDL_GetPerformanceCounter() * 1000.0 / SDL_GetPerformanceFrequency()) - startTime;
	accumulator += (currentTime - lastTime);

	// If we are 3 frames behind, reset _accumulator so we avoid the spiral of death'
	if (accumulator > (3 * desiredTickTime))
		accumulator = 0.0;
}


bool World::readyToTick() {
	return accumulator >= 0.0;
}


void World::incrementTickCounter() {
	++gameTicks;
	accumulator -= desiredTickTime;
}
