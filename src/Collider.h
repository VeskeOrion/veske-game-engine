#ifndef COLLIDER_H
#define COLLIDER_H

#include "Math.h"
#include "Component.h"

class Collider : public Component {
public:
    Collider();
    virtual ~Collider();

    Vector aabb;

    virtual void init();
    virtual void destroy();
    virtual void pretick();
    virtual void tick();
    virtual void posttick();
};

#endif // COLLIDER_H