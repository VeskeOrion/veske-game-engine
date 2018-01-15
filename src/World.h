#ifndef WORLD_H
#define WORLD_H


#include <list>
#include <memory>
#include "Entity.h"


class World {
public:
	World();
	~World();

	// Possible members
	// Level currentLevel;

	// Entity management
	std::list<std::shared_ptr<Entity>> entities; // could this be an array?

	Entity & createEntity(Entity * e);
	std::shared_ptr<Entity> findEntity(Entity & e);
	void destroyEntity(Entity * e);

	// TODO so ugly, move?
	//template <typename T, typename... Args>
	//Entity & World::createEntity(Args&&... args) {
	//  TODO this wont work I'm sure
	//	std::shared_ptr<Entity> e = std::make_shared<Entity>(args);
	//}

	// Level management
	// loadLevel
	// setLevel
	// closeLevel
	// initializeLevel

	// Loop Logic
	bool done; // TODO figure out what to actaully make this
	int gameTicks;
	double startTime;
	double currentTime;
	double timeOfLastTick;
	double accumulator;
	const double desiredTickTime = 1000.0 / 60.0;

	void tick();
	void render();
	void init();
	void run();
	void initializeGameTime();
	void updateGameTime();
	bool readyToTick();
	void incrementTickCounter();
	void processInput();
};


#endif // WORLD_H