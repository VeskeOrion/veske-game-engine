#ifndef BODY_H
#define BODY_H

#include "Component.h"
#include "Math.h"

class Body : public Component {
public:
    Body();
    ~Body();

    Vector vel; // Velocity, affects pos, affected by acc, can be set
	Vector acc; // Acceleration, affects vel, can be set
	Vector drag; // Decceleration, affects vel, always on, can be set

    Vector gravity;
    bool useGravity;

    void init();
    void destroy();
    void pretick();
    void tick();
    void posttick();

    // Vector center();
};

#endif // BODY_H