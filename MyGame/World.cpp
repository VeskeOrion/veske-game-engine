#include "World.h"
#include "Game.h"

#include "Player.h" // TODO remove this, this is for debug testing by spawning players


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

	Entity * e = new Entity();
	e->pos.addX(100);
	Game::world->addEntity(e);
	e->name = "Entity";
	e->sprite.loadFromFile("colorful.png", 64, 64);
	e->sprite.addAnim("fun", 0, true, {0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0});
	e->sprite.setAnim("fun");

	// TODO remove this hardcoded adding player, should be done from a Level object
	std::shared_ptr<Entity> p = Game::world->addEntity(new Player());
	p->name = "Player";
	p->drag.set(1.0f, 1.0f);
	p->sprite.loadFromFile("Character.png", 48, 48);
	p->size.set(48, 48);

	//p->sprite.loadFromFile("Character.png", 48, 48);
	//p->sprite.setAnim("fun");

	//p->sprite.addAnim("fun2", 0, false, {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3});
	//p->sprite.loadFromFile("Character.png", 48, 48);

	//for (int i = 0; i < 100; ++i) {
	//	std::shared_ptr<Entity> k = Game::world->addEntity(new Player());
	//	k->pos.set((int)random(-200.0f, 200.0f), (int)random(-200.0f, 200.0f));
	//	k->sprite.loadFromFile("Character.png", 48, 48);
	//	k->drag.set(.3f, .3f);
	//}
	//Game::world->removeEntity(p.get());

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
	
	// TODO how to order ticks?
	for (auto & e : entities) {
		if (e->active) {
			e->pretick();
		}
	}

	for (auto & e : entities) {
		if (e->active) {
			e->tick();
		}
	}

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
