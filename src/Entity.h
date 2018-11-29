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


#include <vector>
#include <memory>

#include "Math.h"
#include "Sprite.h"

//#include "Collision.h"

class Component;

class Entity {
public:

	Entity(); // TODO private constructors? Could that help?
	virtual ~Entity();

	static unsigned int entityIDCounter;
	unsigned int entityID;

	// a pointer to this entity in the World's entity list, never set this manually
	std::weak_ptr<Entity> thisEntity;

	std::vector<std::shared_ptr<Component>> components;

	std::string name;
	Vector pos;

	bool active;


	// bool useGravity;

	// //Sprite sprite;
	// int zIndex;
	// bool visible;
	// float alpha;
	// TODO float scrollFactor;

	// TODO give Entity an Start? function (like Unity's Start) called when world inits after lvel load, GENIUS!

	// TODO worry about parenting and children
	//std::weak_ptr<Entity> parent;
	//std::list<std::weak_ptr<Entity>> children;

	// integrate
	// handle collisions
	// update


	virtual void init();
	virtual void pretick();
	virtual void tick();
	virtual void posttick();
	virtual void destroy();

	template <typename T>
	std::shared_ptr<T> getComponent() {
		for (unsigned int i = 0; i < components.size(); ++i)
			if (std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(components[i]))
				return t;
		return nullptr;
	}

	template <typename T>
	void addComponent(std::shared_ptr<T> component) {
		component->entity = thisEntity;
		components.push_back(component);
	}
};


#endif // ENTITY_H