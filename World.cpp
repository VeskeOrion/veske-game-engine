#include "World.h"
#include "Game.h"

#include "Player.h" // TODO remove this


World::World() {

}


World::~World() {

}


std::shared_ptr<Entity> World::addEntity(Entity * e) {
	std::shared_ptr<Entity> esp;
	if (findEntity(e) == nullptr) {
		esp.reset(e);
		entities.push_back(esp);
	}

	return esp;
}


std::shared_ptr<Entity> World::findEntity(Entity * e) {
	std::shared_ptr<Entity> r;
	for (auto i = entities.begin(); i != entities.end(); ++i) {
		if ((*i)->entityID == e->entityID)
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
	
	// PUT CODE FOR ADDING DEBUG ENTITIES HERE


	// TODO remove this hardcoded adding player, should be done from a Level object
	std::shared_ptr<Entity> p = Game::world->addEntity(new Player());
	p->sprite.loadFromFile("colorful.png", 64, 64);
	p->sprite.addAnim("fun", 1, true, {0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0});
	p->sprite.setAnim("fun");
	p->sprite.setAnim("goop");
	//Game::world->removeEntity(p.get());

	Game::logger << p->sprite.currentAnim.elapsed;

	Entity * e = new Entity();
	e->pos.addX(100);
	Game::world->addEntity(e);
	//Game::world->removeEntity(e);
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
		e->pretick();
	}

	for (auto & e : entities) {
		e->tick();
	}

	for (auto & e : entities) {
		e->posttick();
	}

	// Remove dead entities
	for (auto i : deadEntities)
		entities.remove(i);
	deadEntities.clear();

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
