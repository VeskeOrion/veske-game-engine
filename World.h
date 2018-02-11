//----------------------------------------------------------------------------------------//
// World.h
// Contains a class that represents the game world. All Entities, when created, have a
// position in the World, and the World manages the creating and deletion of all Entities.
// All of the Entities in the game are stored in the entities list in the World. This class
// is also responsible for loading Levels (in development), which contains Entities, Lights
// (in development), and Terrain (in development), and is responsible for calling every
// Entity's tick() method. The World ticks at constant time intervals, and the timestep is
// contstant as well.
// Access this class via Game::world.
//----------------------------------------------------------------------------------------//


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
	const double desiredFrameRate = 60.0;
	const double desiredTickTime = 1000.0 / desiredFrameRate;

	void init();
	void run();
	void tick();
	void render();
	void processInput();
	void initializeGameTime();
	bool readyToTick();
	void updateGameTime();
	void incrementTickCounter();
};


#endif // WORLD_H