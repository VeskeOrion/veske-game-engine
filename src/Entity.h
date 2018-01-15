#ifndef ENTITY_H
#define ENTITY_H

#include "Math.h"
#include "Image.h"
#include <memory>
#include <list>

class Entity {
public:
	Entity(); // TODO private constructors? Could that help?
	~Entity();

	static unsigned int entityIDCounter;
	unsigned int entityID;

	Vector pos; // Position
	Vector vel; // Velocity
	Vector acc; // Acceleration

	Image image;
	int zIndex;

	bool active;
	bool visible;

	std::weak_ptr<Entity> parent;
	std::list<std::weak_ptr<Entity>> children;

	void pretick();
	void tick();
	void posttick();

	// TODO remove these, make Rectangle fulfil these reponsibilities? Or nah?
	//bool intersects(Entity & e);
	//Vector intersectsAt(Entity & e);
};

#endif // ENTITY_H