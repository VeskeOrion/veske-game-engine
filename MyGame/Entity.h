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


class Entity {
public:
	Entity(); // TODO private constructors? Could that help?
	virtual ~Entity();

	static unsigned int entityIDCounter;
	unsigned int entityID;

	std::string name;

	Vector pos; // Position, top left
	Vector vel; // Velocity
	Vector acc; // Acceleration
	Vector drag; // Decceleration ratio

	Vector size; // AABB size

	Sprite sprite;
	int zIndex;
	bool visible;
	float alpha;

	bool active;

	std::weak_ptr<Entity> parent;
	std::list<std::weak_ptr<Entity>> children;

	// Pretick is for collisions, animations, and "enginey" stuff
	virtual void pretick();

	// Tick is where game logic is updated and physics are reacted to. Always call
	// Entity::tick() as the first thing you do when overriding this function.
	virtual void tick();

	// Posttick has little use as of now.
	virtual void posttick();

	// Destroys this entity once the frame has ended
	virtual void kill();

	// TODO remove these, make Rectangle fulfil these reponsibilities? Or nah?
	//bool intersects(Entity & e);
	//Vector intersectsAt(Entity & e);
};


#endif // ENTITY_H