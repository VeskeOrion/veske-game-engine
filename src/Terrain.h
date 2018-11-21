// #ifndef TERRAIN_H
// #define TERRAIN_H

// #include <memory>
// #include <vector>


// #include "Game.h"
// #include "Entity.h"


// // Heightmap of points that define a (potentially) rugged terrain surface
// class Terrain : public Entity {
// public:
// 	Terrain();
// 	~Terrain();

// 	void init();
// 	void readFromFile();
// 	void generateRandomSmoothTerrain(unsigned int len = 100, unsigned int res = 1);
// 	void generateFlatTerrain(unsigned int len = 100, unsigned int res = 1);

// 	int resolution; // distance between heightmap nodes
// 	std::vector<unsigned int> heightMap;

// 	Orientation orientation; // allow upside down terrain
// 	Vector startPos; // The leftmost position of this terrain

// 	// we have an array/list of points (uniformly distributed?)
// 	// we can determine where the player is by their center being between
// 	// any two points in the heightmap array
// 	// we can determine the slope between those two points and
// 	// if the heightmap is uniformly distributed we can instantly know where
// 	// the player is colliding with it
// 	// constant time collision detection with a huge terrain
// 	// as in the length of the terrain does not factor into the time check
// 	// if an entity is colliding with it
// 	// we can also determine the slope of the terrain (take y difference of the
// 	// two points that 'box in' the player. If player is bigger than terrain resolution?
// 	// terrain resolution can be set and mathed out.
// 	// if an entity is bigger than the terrain resolution, they can.... fuck

// 	// okay, a collision check between an entity and terrain will take time
// 	// proportional to the ratio between the entity and the resolution of the heightmap
// 	// a GIANT wide enemy will have to check for large spikes underneath them, perhaps
// 	// they cover 4 heightmap entries. Will have to loop over all of them under him and
// 	// determine where to put big boy.

// 	// Maybe i can get by by doign this:
// 	// consider the slope to the

// 	// okay what if I didnt work with slopes here
// 	// everything is pixels anyways
// 	// everything is stairsteppy, and entities have a step height
// 	// they can only step up differences in the heigtmap less than their step height
// 	// otherwise and entity will rest upon the highest height that their size encompases
// 	// as in, entities can stand in thin spikes in the heightmap
// 	// step height can be resolved by finding the bottom of the entity currently
// 	// (remember that entity rests on highest point under it) and determining the
// 	// difference in height between its corner and the points in the heightmap directly
// 	// to sides of it. These are the two closest points in the heightmap that the entity
// 	// is not standing over.

// };

// #endif // TERRAIN_H