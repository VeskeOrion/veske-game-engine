//----------------------------------------------------------------------------------------//
// Entity.h
// Contains a class that represents a physical object in the World. Entities will have a
// position, velocity, acceleration, ID, an Image representation, and other various
// properties that physical objects have. Entities can also optionally ahve a parent and/or
// children. If entities have no parent, their positions are relative to the World's (0,0).
// If entities have a parent, their positions are relative to the parent, so if a child does
// not move itself, it will follow the parent exactly.
//----------------------------------------------------------------------------------------//


#ifndef ENTITY_H
#define ENTITY_H


#include <list>
#include <memory>

#include "Math.h"
#include "Sprite.h"

//#include "Collision.h"

class Entity {
public:

	Entity(); // TODO private constructors? Could that help?
	virtual ~Entity();

	static unsigned int entityIDCounter;
	unsigned int entityID;

	// a pointer to this entity in the World's entity list, never set this manually
	std::weak_ptr<Entity> thisEntity;

	// CollisionType collisionType;
	// std::list<std::shared_ptr<Entity>> collisionList; // TODO make this a list of collisions
	// std::list<std::shared_ptr<Collision>> collisionsListed;

	std::string name;

	Vector pos; // Position (top left), affected by vel, can be set
	Vector vel; // Velocity, affects pos, affected by acc, can be set
	Vector acc; // Acceleration, affects vel, can be set
	Vector drag; // Decceleration, affects vel, always on, can be set

	Vector size; // AABB size

	bool active;
	bool useGravity;

	//Sprite sprite;
	int zIndex;
	bool visible;
	float alpha;
	// TODO float scrollFactor;

	// TODO give Entity an Start? function (like Unity's Start) called when world inits after lvel load, GENIUS!

	// TODO worry about parenting and children
	//std::weak_ptr<Entity> parent;
	//std::list<std::weak_ptr<Entity>> children;

	// integrate
	// handle collisions
	// update

	void init();

	// Integrate() is for moving the entity
	virtual void integrate();

	// HandleCollisions() is for solving entity positions after movement
	virtual void handleCollisions();

	// Pretick() is for game logic and has little use as of now
	virtual void pretick();

	// Tick() is where game logic is updated and collisions are reacted to logically
	virtual void tick();

	// Posttick() is for game logic and has little use as of now
	virtual void posttick();

	// Destroys this entity once the frame has ended
	virtual void destroy();

	// Returns if the two entities are intersecting
	virtual bool checkCollision(std::shared_ptr<Entity> e);
};


#endif // ENTITY_H