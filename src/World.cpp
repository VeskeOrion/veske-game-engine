#include <SDL/SDL.h>
#include "World.h"
#include "Game.h"

#include <sstream>
#include <iostream>

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


void World::tick() {
	processInput();
	
	auto i = Game::world->entities.begin();
	for (auto i = Game::world->entities.begin(); i != Game::world->entities.end(); ++i) {
		Entity & cur = **i;
		cur.pretick();
	}

	auto i = Game::world->entities.begin();
	for (auto i = Game::world->entities.begin(); i != Game::world->entities.end(); ++i) {
		Entity & cur = **i;
		cur.tick();
	}

	auto i = Game::world->entities.begin();
	for (auto i = Game::world->entities.begin(); i != Game::world->entities.end(); ++i) {
		Entity & cur = **i;
		cur.posttick();
	}
}


void World::render() {
	Game::renderer->render();
}

// TODO put this in input
void World::processInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
			case SDL_QUIT: {
				done = true;
			} break;

			case SDL_MOUSEMOTION: {

			} break;

			case SDL_MOUSEBUTTONDOWN: {

			} break;

			case SDL_KEYDOWN: {

			}  break;
		}
	}
}