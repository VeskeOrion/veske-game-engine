#ifndef COLLISION_H
#define COLLISION_H


#include <memory>
#include <vector>
#include <list>


class Entity;


// Enum with varying stengths about how entities react to collisions in game
enum CollisionType { KINEMATIC, STRONG, WEAK, TRIGGER, NONE };


class Collision {
public:
	Collision();
	//Collision(std::shared_ptr<const Entity> e1, std::shared_ptr<const Entity> e2);
	~Collision();

	std::shared_ptr<Entity> e1;
	std::shared_ptr<Entity> e2;
};



#endif // COLLISION_H