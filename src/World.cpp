#include "World.h"
#include "Game.h"

#include <algorithm>
#include <vector>
#include <list>
#include <array>

#include "Entity.h" // TODO remove this, this is for debug testing by spawning players
#include "Terrain.h" // TODO remove this, this is for debug testing by spawning players
#include "Collision.h"
#include "Collider.h"
#include "Component.h" // TODO remove this, this is for debug testing by spawning players
#include "Body.h" // TODO remove this, this is for debug testing by spawning players


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


	for (int i = 0; i < 500; ++i) {
		std::shared_ptr<Entity> ent = std::make_shared<Entity>();
		Game::world->addEntity(ent);


		// TODO MUST FIX, entity->thisEntity gets set by world, so components dont have access to it when being aded if they are added before entity is put inot world :C
		std::shared_ptr<Collider> col = std::make_shared<Collider>();
		std::shared_ptr<Body> bod = std::make_shared<Body>();
		ent->addComponent(col);
		ent->addComponent(bod);

		ent->localPos.set(randomNum(-200, 200), randomNum(-200, 200));
		col->aabb.set((int)randomNum(1, 50), (int)randomNum(1, 50));

	}

	// TODO remove this hardcoded adding player, should be done from a Level object
	Game::logger << "Starting to init world\n";

	// k->size.set(32, 32);


	// std::shared_ptr<Player> p(new Player());
	// Game::world->addEntity(p);
	// p->name = "Player";
	// p->drag.set(1.0f, 1.0f);
	// p->size.set(64, 64);

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
			// Game::logger << "Ticked\n";
		}
		render();
		// Game::logger << "Rendered\n";
	}
	Game::logger << "Done\n";
}


void World::tick() {
	//entities.sort(); // TODO write a operator< for entities involving their script execution order

	processInput();

	// Any pre-tick logic
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

	// Any post-tick logic
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

	if (Game::input->getAction(Input::Action::ACTION_CROUCH)) {
		Game::renderer->camera.zoom *= 1.05f;
	}

	if (Game::input->getAction(Input::Action::ACTION_RUN)) {
		Game::renderer->camera.zoom *= 0.95f;
	}

	if (Game::input->getAction(Input::Action::ACTION_LEFT)) {
		Game::renderer->camera.pos.addX(-5.0f * (1.0f / Game::renderer->camera.zoom));
	}

	if (Game::input->getAction(Input::Action::ACTION_RIGHT)) {
		Game::renderer->camera.pos.addX(+5.0f * (1.0f / Game::renderer->camera.zoom));
	}

	if (Game::input->getAction(Input::Action::ACTION_UP)) {
		Game::renderer->camera.pos.addY(-5.0f * (1.0f / Game::renderer->camera.zoom));
	}

	if (Game::input->getAction(Input::Action::ACTION_DOWN)) {
		Game::renderer->camera.pos.addY(+5.0f * (1.0f / Game::renderer->camera.zoom));
	}



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
	collisionChecks = 0; // TODO remove
	partitions = 0; // TODO remove

	// pairwiseDetectCollisions();
	quadTreeDetectCollisions();

	std::cout << "Checked " << collisionChecks << " in " << partitions << " partitions." << std::endl;
}


void World::pairwiseDetectCollisions() {
	//Slow pair-by-pair collision detection
	// for (std::shared_ptr<Entity> i : entities) {
	// 	for (std::shared_ptr<Entity> j : entities) {
	// 		if (i != j) {
	// 			++collisionChecks;
	// 			Collider * coli = i->getComponent<Collider>();
	// 			Collider * colj = j->getComponent<Collider>();
	// 			if (coli && colj && coli->broadIsColliding(colj)) {
	// 				coli->isColliding = true;
	// 				colj->isColliding = true; // TODO revamp
	// 			}
	// 		}
	// 	}
	// }
	std::vector<Collider *> allColliders;
	std::for_each(entities.begin(), entities.end(),
		[&allColliders] (std::shared_ptr<Entity> entity) {
			std::vector<Collider *> entityColliders = entity->getComponents<Collider>();
			allColliders.insert(allColliders.end(), entityColliders.begin(), entityColliders.end());
		}
	);
	for (Collider * col : allColliders) {
		col->isColliding = false;
	}
	for (Collider * col1 : allColliders) {
		for (Collider * col2 : allColliders) {
			if (col1 != col2) {
				++collisionChecks;

				if (col1->broadIsColliding(col2)) {
					col1->isColliding = true;
					col2->isColliding = true;
				}
			}
		}
	}
}


void World::quadTreeDetectCollisions() {
	// quadrants are numbered in the same way, based on pos and neg, like a cartesian graph

	// find initial world size (linear)
	int minX, maxX, minY, maxY;
	minX = maxX = entities.front()->pos().x();
	minY = maxY = entities.front()->pos().y();
	
	for (std::shared_ptr<Entity> e : entities) {
		minX = e->pos().x() < minX ? e->pos().x() : minX;
		maxX = e->pos().x() > maxX ? e->pos().x() : maxX;
		minY = e->pos().y() < minY ? e->pos().y() : minY;
		maxY = e->pos().y() > maxY ? e->pos().y() : maxY;
	} // TODO swap these e->pos() out for a loop over collider->pos ??? necessary?
	
	// create list of all colliders
	std::vector<Collider *> allColliders;
	for (std::shared_ptr<Entity> entity : entities) {
		std::vector<Collider *> entityColliders = entity->getComponents<Collider>();
		allColliders.insert(allColliders.end(), entityColliders.begin(), entityColliders.end());
	}
	// std::for_each(entities.begin(), entities.end(),
	// 	[&allColliders] (std::shared_ptr<Entity> entity) {
	// 		std::vector<Collider *> entityColliders = entity->getComponents<Collider>();
	// 		allColliders.insert(allColliders.end(), entityColliders.begin(), entityColliders.end());
	// 	}
	// );

	for (Collider * col : allColliders) {
		col->isColliding = false; // TODO remove
	}
	

	partitionWorldAndCheckCollisions(allColliders, minX, maxX, minY, maxY);
}

void World::partitionWorldAndCheckCollisions(const std::vector<Collider *> & collidersInPartition, int minX, int maxX, int minY, int maxY, unsigned int partitionSize) {
	if (collidersInPartition.size() < 2)
		return;
	
	// lots of large entities significantly affect the performance of this, big entities will
	// get put in pretty much every quadrants' collider list, and get checked by each list
	// multiuple times (MORE TIMES THAN JUST PAIRWISE!)
	// quad tree performs best when there are not lots of active collisions
	// performs worse than pairwise if jam packed
	// TODO decide magic number of colliders its OK to loop over
	if ((maxX - minX <= partitionSize && maxY - minY <= partitionSize) || collidersInPartition.size() == 2) {
		// TODO check early here if 2 entities
		++partitions;
		for (Collider * col1 : collidersInPartition) {
			for (Collider * col2 : collidersInPartition) {
				if (col1 != col2) {
					++collisionChecks;
					if( col1->broadIsColliding(col2)) {
						col1->isColliding = true;
						col2->isColliding = true; // TODO revamp
					}
				}
			}
		}
	}
	else {
		// recursive case, make vectors of all colliders in the same partition
		int midX = (maxX - minX) / 2 + minX;
		int midY = (maxY - minY) / 2 + minY;

		std::array<std::vector<Collider *>, 4> quadrants;
		for (Collider * c : collidersInPartition) {
			// need entity world pos + collider offset to do this math :(
				Vector curPos = c->pos();
				if (curPos.x() < midX && curPos.y() < midY) { // top left is in quad 3
					quadrants.at(2).push_back(c);
				}
				if (curPos.x() + c->aabb.x() >= midX && curPos.y() < midY) { // top right is in quad 4
					quadrants.at(3).push_back(c);
				}
				if (curPos.x() < midX && curPos.y() + c->aabb.y() >= midY) { // bot left is in quad 2
					quadrants.at(1).push_back(c);
				}
				if (curPos.x() + c->aabb.x() >= midX && curPos.y() + c->aabb.y() >= midY) { // bot right is in quad 1
					quadrants.at(0).push_back(c);
				}
		}

		partitionWorldAndCheckCollisions(quadrants.at(0), midX, maxX, midY, maxY);
		partitionWorldAndCheckCollisions(quadrants.at(1), minX, midX, midY, maxY);
		partitionWorldAndCheckCollisions(quadrants.at(2), minX, midX, minY, midY);
		partitionWorldAndCheckCollisions(quadrants.at(3), midX, maxX, minY, midY);
	}
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
