#include "World.h"
#include "Game.h"

#include "Entity.h" // TODO remove this, this is for debug testing by spawning players
#include "Player.h" // TODO remove this, this is for debug testing by spawning players
#include "Terrain.h" // TODO remove this, this is for debug testing by spawning players
#include "Collision.h"


World::World() {

}


World::~World() {

}


std::shared_ptr<Entity> World::addEntity(std::shared_ptr<Entity> e) {
	if (findEntity(e) == nullptr) {
		e->thisEntity = e; // assigns the thisEntity pointer in the entity to the global one
		entities.push_back(e);
	}

	return e;
}


// Queues an entity deletion until the end of the update, when it is actually deleted
void World::removeEntity(std::shared_ptr<Entity> e) {
	std::shared_ptr<Entity> foundEntity = findEntity(e);
	if (foundEntity)
		deadEntities.push_back(foundEntity);
}


std::shared_ptr<Entity> World::findEntity(std::shared_ptr<Entity> e) {
	std::shared_ptr<Entity> r = nullptr;
	for (auto i : entities) {
		if (i->entityID == e->entityID)
			r = i;
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


void World::init() {
	done = false;

	//setLevel();
	//loadLevel();
	//initializeLevel();
	
	////**************************************************************************////
	// PUT DEBUG WORLD INITIALIZATION CODE HERE


	// TODO remove this hardcoded adding player, should be done from a Level object
	Game::logger << "Starting to init world\n";
	std::shared_ptr<Entity> k(new Entity());
	k->size.set(32, 32);

	Game::world->addEntity(k);

	std::shared_ptr<Player> p(new Player());
	Game::world->addEntity(p);
	p->name = "Player";
	p->drag.set(1.0f, 1.0f);
	p->size.set(64, 64);

	// for (int i = 0; i < 20; ++i) {
		// std::shared_ptr<Entity> k(new Entity());
		// Game::world->addEntity(k);
	// 	k->useGravity = false;

	// 	if (random() > 0.95f) {
	// 		k->pos.addX(100);
	// 		k->sprite.loadFromFile("media/colorful.png", 64, 64);
	// 		k->size.set(64, 64);
	// 		if (random() > 0.5f)
	// 			k->sprite.addAnim("fun", 0, true, { 0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0 });
	// 		else
	// 			k->sprite.addAnim("fun", 0, true, { 0,1,1,2,2,2,2,2,3,3,2,2,2,3,2,1,0,0,1,1 });
	// 		k->sprite.setAnim("fun");
	// 	}
	// 	else if (random() > 0.5f) {
	// 		k->sprite.loadFromFile("media/Wheel.png", 8, 8);
	// 		k->size.set(8, 8);
	// 	}
	// 	else {
	// 		k->sprite.loadFromFile("media/Character.png", 48, 48);
	// 		k->size.set(48, 48);
	// 	}

	// 	k->pos.set(random(-200.0f, 200.0f), random(-200.0f, 200.0f));
	// }
	// //Game::world->removeEntity(p.get());

	// std::shared_ptr<Player> p(new Player());
	// Game::world->addEntity(p);
	// p->name = "Player";
	// p->drag.set(1.0f, 1.0f);
	// p->sprite.loadFromFile("media/Colorful.png", 64, 64);
	// p->size.set(64, 64);

	// std::shared_ptr<Terrain> t(new Terrain());
	// Game::world->addEntity(t);
	// t->name = "Terrain";
	// t->generateRandomSmoothTerrain(500,1);
	// t->sprite.loadFromFile("media/FlatTerrain.png", 500, 1);
	// for (unsigned int i = 0; i < t->heightMap.size(); ++i) {
	// 	Game::logger << t->heightMap.at(i) << " ";
	// }

	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "You fucked up", "Here is the game", Game::window->sdl_window);

	// PUT DEBUG WORLD INITIALIZATION CODE HERE
	Game::logger << "Fully inited world\n";
	////**************************************************************************////
}


void World::run() {
	initializeGameTime();

	while (!done) {
		updateGameTime();

		if (readyToTick()) {
			tick();

			incrementTickCounter();
			Game::logger << "Ticked\n";
		}
		render();
		Game::logger << "Rendered\n";
	}
	Game::logger << "Done\n";
}


void World::tick() {
	//entities.sort(); // TODO write a operator< for entities involving their script execution order

	processInput();
	
	// Move entities, integrate velocity
	for (auto & e : entities) {
		if (e->active) {
			e->integrate();
		}
	}

	// Detect collisions
	populateCollisionLists();

	// Solve entity positions after collisions
	for (auto & e : entities) {
		if (e->active) {
			e->handleCollisions();
		}
	}

	// Any pre-tick logic (very rarely used)
	for (auto & e : entities) {
		if (e->active) {
			e->pretick();
		}
	}

	// Apply game logic, react to collisions
	for (auto & e : entities) {
		if (e->active) {
			e->tick();
		}
	}

	// Any post-tick logic (very rarely used)
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

	// if (findEntity("Player")->collisionList.size() != 0) {
	// 	Game::logger << findEntity("Player")->collisionList.size() << "cols: ";
	// 	for (auto & e : findEntity("Player")->collisionList) {

	// 		Game::logger << e->name << " ";
	// 	}

	// 	Game::logger << "\n";
	// }

	//Game::renderer->camera.zoom += Game::input->getMovementAxes().yf() * 0.1;

	// TODO remove this, but if I have to put world testing things here
	//for (auto & k : Game::input->tappedKeys)
		//Game::logger << k << "\n";
	//Game::logger << findEntity("Player")->pos.xf() << " " << findEntity("Player")->pos.yf() << "\n";
	//
	//if (entities.size() > 0)
	//	entities.back()->kill();
	//Game::logger << randomNum() << "\n";

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
	// for (auto & i : entities) {
	// 	i->collisionList.clear();
	// 	for (auto & j : entities) {
	// 		if (i !=j && i->checkCollision(j)) {
	// 			i->collisionList.push_back(j); // TODO make collision objects instead
	// 		}
	// 	}
	// }
}


void World::initializeGameTime() {
	startTime = (SDL_GetPerformanceCounter() * 1000.0 / SDL_GetPerformanceFrequency());
	currentTime = (SDL_GetPerformanceCounter() * 1000.0 / SDL_GetPerformanceFrequency()) - startTime;
	timeOfLastTick = currentTime;
	gameTicks = 0;
	accumulator = 0.0;
}


void World::updateGameTime() {
	double lastTime = currentTime;
	currentTime = (SDL_GetPerformanceCounter() * 1000.0 / SDL_GetPerformanceFrequency()) - startTime;
	accumulator += (currentTime - lastTime);

	// If we are 3 frames behind, reset accumulator so we avoid the spiral of death
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
