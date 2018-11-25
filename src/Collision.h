#ifndef COLLISION_H
#define COLLISION_H


#include <memory>
#include <vector>
#include <list>

#include "Entity.h"


// // Enum with varying stengths about how entities react to collisions in game
// enum CollisionType { KINEMATIC, STRONG, WEAK, TRIGGER, NONE };


class Collision {
public:
	Collision();
	Collision(std::vector<std::shared_ptr<Entity>> & entities);
	~Collision();

	std::vector<std::shared_ptr<Entity>> entities;

	void init();
	void destroy();
};



#endif // COLLISION_H