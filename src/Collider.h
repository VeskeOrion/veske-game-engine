#ifndef COLLIDER_H
#define COLLIDER_H

#include <memory>
#include <vector>

#include "Math.h"
#include "Component.h"

class Collider : public Component {
public:
    Collider();
    virtual ~Collider();

    Vector aabb;
    //Vector localOffset;

    bool isColliding = false; // TODO remove

    virtual void init();
    virtual void destroy();
    virtual void pretick();
    virtual void tick();
    virtual void posttick();

    Vector pos();

    bool broadIsColliding(Collider * col);
    //virtual std::vector<Vector> getAxes(Collider * col = nullptr);
};

#endif // COLLIDER_H