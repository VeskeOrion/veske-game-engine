#include "World.h"
#include "Game.h"


World::World() {

}


World::~World() {

}


Entity & World::createEntity(Entity * e) {
	std::shared_ptr<Entity> esp(e);
	entities.push_back(esp);

	return *esp;
}


std::shared_ptr<Entity> World::findEntity(Entity & e) {
	std::shared_ptr<Entity> r;
	for (auto i = entities.begin(); i != entities.end(); ++i) {
		if ((*i)->entityID == e.entityID)
			r = *i;
	}
	return r;
}


void World::destroyEntity(Entity * e) {
	// TODO write this
}


void World::init() {
	//setLevel();
	//loadLevel();
	//initializeLevel();
	
	Entity * e = new Entity();
	e->pos.addX(100);
	Game::world->createEntity(e);
	Game::world->createEntity(new Entity());
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

	for (auto & e : entities) {
		e->pretick();
	}

	for (auto & e : entities) {
		e->tick();
	}

	for (auto & e : entities) {
		e->posttick();
	}

	// TODO remove this, but if I have to put world testing things here
	for (auto & k : Game::input->tapped)
		Game::logger << k << "\n";
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
